# Arduino Projects

## Project 1  Position Sensing of an Object on Cantilevers

The project precisely sensed the position of a moving object on a cantilever. Different positions of the object caused slightly different deformation of the cantilever, and it is measured by strain gauges and a bridge circuit. The system looks like [this](https://drive.google.com/file/d/1OnwcsgjhRVHfMfDv9uaYfL2xoI8uK0y3/view?usp=sharing). While caliberating the sensors, we wrote the "motor" code to control a step motor which accurately drives the object to different locations on the cantilever through a ball screw structure. 

Electronic compoments:
MCU - Arduino Uno; Motor driver - L298N

Time:
2018.09 - 2018.10

&emsp;

## Project 2  Intelligent Transport Vehicle

The project programmed on a tracked robot platform with a 4 DOF manipulator arm manufactured by [XiaoR Geek Technology](http://www.xiao-r.com/) to do indoor object transport tasks. The robotic vehicle can track lines on the floor, detect the distance from the object, grab the object safely and accurately with the manipulator, and transport it along the given path. The "vehicle" code is the main program that controls the vehicle to do the above tasks. The "communication" code does the serial communication between the MCU and the WIFI board, so we can send start/stop signal to the robot through wireless communication from a remote PC. A video showing the robot working can be viewed [here](https://drive.google.com/file/d/1z-GXwpnpFih6BSsvr7h7rup-JnhHg6_W/view?usp=sharing).

Electronic compoments:
MCU - Arduino MEGA2560; WIFI board - Robot-Link V4.0 AR WIFI module

Time:
2018.10 - 2018.12

<img src="https://github.com/tiansy97/Arduino-projects/raw/master/project%202/vehicle.png" width="300">
