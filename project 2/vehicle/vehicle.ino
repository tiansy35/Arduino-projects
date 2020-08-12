#include <Servo.h>
#include <EEPROM.h>
#define SIZE(a) sizeof(a) / sizeof(a[0])

int flag = 0;                       // function flag
int adjust = 1;                      // motor flag
int ENA = 5;                        // L298 enable A
int ENB = 6;                        // L298 enable B
int INPUT2 = 7;                     // connect to motor 2
int INPUT1 = 8;                     // connect to motor 1
int INPUT3 = 12;                    // connect to motor 3
int INPUT4 = 13;                    // connect to motor 4 
int Input_Detect_LEFT = A13;        // left infrared sensor (detector)
int Input_Detect_RIGHT = A14;       // left infrared sensor (detector)
int IR_L;                          // flag for the left IR sensor                          
int IR_R;                          // flag for the right IR sensor
int Left_Speed_Hold = 255;           
int Right_Speed_Hold = 255;          

int Echo = A5;                       // ultrasonic signal receive pin
int Trig = A4;                       // ultrasonic signal emit pin

int buffer[3];                       // serial communication buffer
int rec_flag = 0;                        // serial communication flag
int serial_data;                     // serial data
unsigned long Costtime;              

int mark = 0;

Servo servo1;                     
Servo servo2;                       
Servo servo3;                       
Servo servo4;                       

// Initial position of the manipulator
int a = 120;
int b = 90;
int c = 30;
int d = 180;

int dir = 1;

#define MOTOR_GO_FORWARD  {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}      // move forward                              
#define MOTOR_GO_BACK     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}      // move backward
#define MOTOR_GO_RIGHT    {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}      // turn right
#define MOTOR_GO_LEFT     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}      // turn left
#define MOTOR_GO_STOP     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}        // stop        

void setup()
{
  pinMode(ENA, OUTPUT);     
  pinMode(ENB, OUTPUT);     
  pinMode(INPUT1, OUTPUT);  
  pinMode(INPUT2, OUTPUT);  
  pinMode(INPUT3, OUTPUT);  
  pinMode(INPUT4, OUTPUT);  
  
  pinMode(Input_Detect_LEFT,INPUT);
  pinMode(Input_Detect_RIGHT,INPUT);

  analogWrite(ENA, 155);
  analogWrite(ENB, 155);
 
  servo1.attach(11);
  servo2.attach(2);
  servo3.attach(4);        
  servo4.attach(3);
  
  servo1.write(a);
  servo2.write(b);
  servo3.write(c);
  servo4.write(d);
   
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
 
  USART_init();                           // initialize serial communication and interrupts 
}

void TrackLine()   // line tracking mode
{
  IR_L = digitalRead(Input_Detect_LEFT);
  IR_R = digitalRead(Input_Detect_RIGHT);

  if ((IR_L == HIGH) && (IR_R == HIGH))  // if the two sensors detect the line, it is a stop sign
  {
    MOTOR_GO_STOP;  // stop
    delay(1000);
    flag = 1;
  }
  
  if ((IR_L == HIGH) && (IR_R == LOW)) // if the left sensor detects the line, turn left
  {
    MOTOR_GO_LEFT;
    delay(100);
  }
  
  if ((IR_L == LOW) && ( IR_R == HIGH)) // if the right sensor detects the line, turn right
  {
    MOTOR_GO_RIGHT;
    delay(100);
  }
  
  // if none of the sensor detects the line, the vehicle is on the right path and should keep going forward
  if ((IR_L == LOW) && (IR_R == LOW)) 
  {
    MOTOR_GO_FORWARD;
  }
  
}

char Get_Distance() // get the distance from ultrasonic sensor
{
  digitalWrite(Trig, LOW);   // keep the trig signal low for 2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // send a high trig signal 
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    
  
  float Ldistance = pulseIn(Echo, HIGH,5000);  // read the time difference between the signal sent and the signal received
  Ldistance = Ldistance / 5.8 / 10; // compute distance from the time difference (unit:cm)

  return Ldistance;
}

void Take()
{
  // Adjust distance to the object in order to safely grasp it
  while ((Get_Distance() < 19)||(Get_Distance() > 20.5))
  {
      if (Get_Distance() < 19) 
      { 
        MOTOR_GO_BACK;
        delay(20);
      }
      if (Get_Distance() > 20.5) 
      { 
        MOTOR_GO_FORWARD;
        delay(20);
      }      
  }
  
  // Stop the motors
  digitalWrite(ENA, LOW);  
  digitalWrite(ENB, LOW);  
  
  // Manipulation steps
  // Step 1
  while (c < 120) 
  {
    servo3.write(c);
    c++;
    delay(20);
  }
  // Step 2
  while ((a > 100) || (d > 120))
  {
    servo1.write(a);
    servo4.write(d);
    if (a > 100) a--;
    if (d > 120) d--;
    delay(20);
  }
  delay(1000);
  // Step 3
  while (a < 150) 
  {
    servo1.write(a);
    a++;
    delay(20);
  }
  delay(1000);
  // Step 4
  while (d < 170) 
  {
    servo4.write(d);
    d++;
    delay(20);
  }
  while (c > 30)
  {
      servo3.write(c); 
      c--;
      delay(20);
  } 
  delay(1000); 
  
  analogWrite(ENA, 155);  
  analogWrite(ENB, 155);  
  
}  

void Turn_Around()
{  
  analogWrite(ENA, 255);  // the robot at full speed
  analogWrite(ENB, 255);  
  
  MOTOR_GO_RIGHT;  // make a right turn about 180 degrees 
  delay(2000);
  MOTOR_GO_FORWARD;
  delay(200);
  
  analogWrite(ENA, 155);  // the robot at lower speed
  analogWrite(ENB, 155);  
}

void loop()
{
  UartTimeoutCheck();                   
  while (mark)    // while the remote signal tells the robot to move 
  {
    switch (flag)
    {
      case 0:     TrackLine(); return; // line tracking mode
      case 1:     Take(); flag = 2; return;     // manipulation mode
      case 2:     Turn_Around(); flag = 0; return; // turn around and keep tracking lines
    }
    
  }
  MOTOR_GO_STOP;
}


