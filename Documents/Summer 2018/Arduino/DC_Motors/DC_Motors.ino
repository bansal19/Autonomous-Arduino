#include "Studuino.h" // Studuino header file
#include <NewPing.h>

// Studuino board image. Make only one per program.
Studuino board;

byte echoLeftSensor = 11;
byte trigLeftSensor = 12;

byte echoRightSensor = 6;
byte trigRightSensor = 7;

byte echoMiddleSensor = 9;
byte trigMiddleSensor = 10;

NewPing sonarLeft(trigLeftSensor, echoLeftSensor, 10000);
NewPing sonarRight(trigRightSensor, echoRightSensor, 10000);
NewPing sonarMiddle(trigMiddleSensor, echoMiddleSensor, 10000);

//Function Declaration
int  ChangeZero(int);

// Called once at the start of the program. Primarily used for initialization.
void setup() {
 // Use initialization functions to initialize Studuino ports with parts connected
  board.InitDCMotorPort(PORT_M1); // Initializes port M1 for use with a DC Motor.
  board.InitDCMotorPort(PORT_M2); // Initializes port M2 for use with a DC Motor.
  
//  Serial.begin(9600);

  board.Timer(100);
}


// This function runs an infinite loop. Main process.
void loop() {

int leftSensor = sonarLeft.ping_cm();
int rightSensor = sonarRight.ping_cm();
int middleSensor = sonarMiddle.ping_cm();


leftSensor = ChangeZero(leftSensor);
rightSensor = ChangeZero(rightSensor);
middleSensor = ChangeZero(middleSensor);


if((leftSensor <= 15) && (rightSensor > 15) && (middleSensor > 15))
{
  board.Move(FORWARD_LEFT, 255, 100, COAST);
} else if ((rightSensor <= 15) && (leftSensor > 15) && (middleSensor > 15))
{
  board.Move(FORWARD_RIGHT, 255, 100, COAST);
} else if(middleSensor <= 5)
{
  board.Move(BACKWARD_RIGHT, 255, 800, BRAKE);
} else 
{
  board.Move(FORWARD, 255, 500, COAST);
}

}

int   ChangeZero(int sensor)
{
  if(sensor == 0)
  {
    sensor = 1000;
  }
  return sensor;
}


