int Pin1 = 2;     //Connect I1 pin on the motor driver
int Pin2 = 3;     //Connect I2 pin on the motor driver
int Pin3 = 7;    
int Pin4 = 8;    

int StepCount = 0;
boolean dir = true;      //Direction of motion 
int stepN = 0;
int stepmax = 800*15;


void setup()
{
  pinMode(Pin1, OUTPUT);     //A1
  pinMode(Pin2, OUTPUT);     //A2
 
  pinMode(Pin3, OUTPUT);    //B1
  pinMode(Pin4, OUTPUT);    //B2
 
  Serial.begin(9600);          //Baud rate
}


void OneStep(int numstep)   // 8 Steps in one loop (0-7)
{
    switch(numstep)
  {
    case 0:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;
    case 1:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;
    case 2:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;
    case 3:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;
    case 4:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;
    case 5:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;
      case 6:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;
    case 7:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;
    default:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;
  }

}

 
void loop()
{
  
  if(stepN < stepmax)
  {
  OneStep(StepCount);
  delay(20);
  if(dir)
  {
    StepCount++;    // Move to the next step
    stepN++;
  }
  else{
    StepCount--;
    stepN++;
  }
  if(StepCount>7){  // Reset the step, start from 0
    StepCount=0;
  }
  if(StepCount<0){
    StepCount=7;
  }
  }
  else      
  {
    // After moving for a maximum number of steps, stop the motor
    //stepN=0;
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, LOW);
  }
  
  Serial.println(stepN);

}


