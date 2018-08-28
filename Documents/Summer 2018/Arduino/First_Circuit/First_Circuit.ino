
//#include <Servo.h> // Servomotor header file
//#include <Wire.h> // I2C device header file
//#include <MMA8653.h> // Accelerometer header file
//#include <MPU6050.h> // Gyroscope header file
//#include <IRremoteForStuduino.h> // IR Receiver header file
//#include <ColorSensor.h> // Color Sensor header file
#include "Studuino.h" // Studuino header file

#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))
#define _BV(bit) (1 << (bit))

// Studuino board image. Make only one per program.
Studuino board;

int echoLeftSensor = 9;
int trigLeftSensor = 10;

int echoRightSensor = 6;
int trigRightSensor = 7;

int distance;
int duration;

//Function Declaration
int CalcDistance(const int, const int);

// Called once at the start of the program. Primarily used for initialization.
void setup() {
 // Use initialization functions to initialize Studuino ports with parts connected
  board.InitDCMotorPort(PORT_M1); // Initializes port M1 for use with a DC Motor.
  board.InitDCMotorPort(PORT_M2); // Initializes port M2 for use with a DC Motor.
  pinMode(echoLeftSensor, INPUT);
  pinMode(trigLeftSensor, OUTPUT);
 
  pinMode(echoRightSensor, INPUT);
  pinMode(trigRightSensor, OUTPUT);
  Serial.begin(9600);

  board.Timer(100);
}


// This function runs an infinite loop. Main process.
void loop() {
//  Serial.print("  left: ");
//  Serial.println(CalcDistance(trigLeftSensor, echoLeftSensor));

//  Serial.print("  right: ");
//  Serial.println(CalcDistance(trigRightSensor, echoRightSensor));
  
  if((CalcDistance(trigLeftSensor, echoLeftSensor) > 10) && (CalcDistance(trigRightSensor, echoRightSensor) > 10)) {
      board.Move(FORWARD, 255, 500, COAST);
      
  } else if ((CalcDistance(trigLeftSensor, echoLeftSensor) <= 5) && (CalcDistance(trigRightSensor, echoRightSensor) <= 5)) {
      board.Move(BACKWARD_LEFT, 255, 1000, BRAKE);
      
  } else if(CalcDistance(trigLeftSensor, echoLeftSensor) <= 10 ) {
      board.Move(FORWARD_LEFT, 255, 500, COAST);

  } else if (CalcDistance(trigRightSensor, echoRightSensor) <= 10) {
      board.Move(FORWARD_RIGHT, 255, 500, COAST);
  } 
} 

int CalcDistance(const int trig, const int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(10);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  
  distance = 0;
  distance = duration * 0.034/2;

  return(distance);
}



