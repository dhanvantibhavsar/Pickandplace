//Library Imports
#include <Arduino.h>
#include "BluetoothSerial.h"
//Stepper.h downloaded from arduino.cc, included in lib folder
#include "Stepper.h" 

//Verify Bluetooth has been enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Defining Pin Connections based on Hardware Schematic
//Left Motor Driver Pins 
#define LEFTMOTORPIN1 32
#define LEFTMOTORPIN2 33

//Right Motor Driver Pins
#define RIGHTMOTORPIN1 25
#define RIGHTMOTORPIN2 26

//Elbow Joint Stepper motor driver pin 
#define ELBOWSTEPPERMOTORPIN1 27
#define ELBOWSTEPPERMOTORPIN2 14
#define ELBOWSTEPPERMOTORPIN3 12
#define ELBOWSTEPPERMOTORPIN4 13


//Wrist Joint Stepper motor driver pin
#define WRISTSTEPPERMOTORPIN1 15
#define WRISTSTEPPERMOTORPIN2 2
#define WRISTSTEPPERMOTORPIN3 4
#define WRISTSTEPPERMOTORPIN4 16


//Claw Stepper motor driver pin
#define CLAWSTEPPERMOTORPIN1 17
#define CLAWSTEPPERMOTORPIN2 5
#define CLAWSTEPPERMOTORPIN3 18
#define CLAWSTEPPERMOTORPIN4 19

//Steps Per Revolution= 360/ Stepper motor Angle 
#define stepsPerRevolution 200  //1.8 Angle stepper Motor

//Creating Object for Serial Bluetooth connection
BluetoothSerial SerialBT;

// Creating Object for Stepper motors
Stepper elbowStepper(stepsPerRevolution,ELBOWSTEPPERMOTORPIN1,ELBOWSTEPPERMOTORPIN2,ELBOWSTEPPERMOTORPIN3,ELBOWSTEPPERMOTORPIN4);
Stepper wristStepper(stepsPerRevolution,WRISTSTEPPERMOTORPIN1,WRISTSTEPPERMOTORPIN2,WRISTSTEPPERMOTORPIN3,WRISTSTEPPERMOTORPIN4);
Stepper clawStepper(stepsPerRevolution,CLAWSTEPPERMOTORPIN1,CLAWSTEPPERMOTORPIN2,CLAWSTEPPERMOTORPIN3,CLAWSTEPPERMOTORPIN4);

//Function Decleration
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void elbowJointUp();
void elbowJointDown();
void wristJointUp();
void wristJointDown();
void clawOpen();
void clawClose();
void stopMotor();

//Code Executions Starts here
void setup() {
  Serial.begin(115200); //Setting BAUD rate for Serial Communication 
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  //Defining Pin Modes as output
  pinMode(LEFTMOTORPIN1 , OUTPUT);
  pinMode(LEFTMOTORPIN2, OUTPUT);

  pinMode(RIGHTMOTORPIN1, OUTPUT);
  pinMode(RIGHTMOTORPIN2, OUTPUT);

  pinMode(ELBOWSTEPPERMOTORPIN1, OUTPUT);
  pinMode(ELBOWSTEPPERMOTORPIN2, OUTPUT);
  pinMode(ELBOWSTEPPERMOTORPIN3, OUTPUT);
  pinMode(ELBOWSTEPPERMOTORPIN4, OUTPUT);

  pinMode(WRISTSTEPPERMOTORPIN1, OUTPUT);
  pinMode(WRISTSTEPPERMOTORPIN2, OUTPUT);
  pinMode(WRISTSTEPPERMOTORPIN3, OUTPUT);
  pinMode(WRISTSTEPPERMOTORPIN4, OUTPUT);

  pinMode(CLAWSTEPPERMOTORPIN1, OUTPUT);
  pinMode(CLAWSTEPPERMOTORPIN2, OUTPUT);
  pinMode(CLAWSTEPPERMOTORPIN3, OUTPUT);
  pinMode(CLAWSTEPPERMOTORPIN4, OUTPUT);


}


void loop() {
  //Waiting for Data from Mobile controller over Bluetooth
  if (SerialBT.available()) {
    int serialData = SerialBT.read();
    Serial.write(serialData );
    // Calling Functions based on input commands 
    switch (serialData)
    {
    case '1':
      Serial.write("Moving Forward");
      moveForward();
      break;
    
    case '2':
      Serial.write("Moving Backward");
      moveBackward();
      break;
    
    case '3':
      Serial.write("Turn Left");
      turnLeft();
      break;
    
    case '4':
      Serial.write("Turn Right");
      turnRight();
      break;
    
    case '5':
      Serial.write("Moving Elbow Joint UP");
      elbowJointUp();
      break;
    
    case '6':
      Serial.write("Moving Elbow Joint Down");
      elbowJointDown();
      break;
    
    case '7':
      Serial.write("Moving Wrist Joint UP");
      wristJointUp();
      break;
    
    case '8':
      Serial.write("Moving Wrist Joint Down");
      wristJointDown();
      break;
    
    case '9':
      Serial.write("Opening Claw");
      clawOpen();
      break;
    
    case '10':
      Serial.write("Closing Claw");
      clawClose();
      break;
    
    default:
      Serial.write("Wrong input");
      break;
    }

  }
  delay(20);
}

//Function to move bot forward 
void moveForward() {
digitalWrite(LEFTMOTORPIN1, HIGH);
digitalWrite(LEFTMOTORPIN2, LOW);
digitalWrite(RIGHTMOTORPIN1, HIGH);
digitalWrite(RIGHTMOTORPIN2, LOW);
//Keep motors on for 500 miliseconds
delay(500);
//Stop Motors 
stopMotor();
}

//Function to move bot backward 
void moveBackward() {
digitalWrite(LEFTMOTORPIN1, LOW);
digitalWrite(LEFTMOTORPIN2, HIGH);
digitalWrite(RIGHTMOTORPIN1, LOW);
digitalWrite(RIGHTMOTORPIN2, HIGH);
//Keep motors on for 500 miliseconds
delay(500);
//Stop Motors 
stopMotor();
}

//Function to turn bot left 
void turnLeft() {
digitalWrite(LEFTMOTORPIN1, LOW);
digitalWrite(LEFTMOTORPIN2, HIGH);
digitalWrite(RIGHTMOTORPIN1, HIGH);
digitalWrite(RIGHTMOTORPIN2, LOW);
//Keep motors on for 500 miliseconds
delay(500);
//Stop Motors 
stopMotor();
}

//Function to turn bot right 
void turnRight() {
digitalWrite(LEFTMOTORPIN1, HIGH);
digitalWrite(LEFTMOTORPIN2, LOW);
digitalWrite(RIGHTMOTORPIN1, LOW);
digitalWrite(RIGHTMOTORPIN2, HIGH);
//Keep motors on for 500 miliseconds
delay(500);
//Stop Motors 
stopMotor();
}

//Function to move Elbow Joint Up
void elbowJointUp() {
elbowStepper.step(3);
}

//Function to move Elbow Joint Down 
void elbowJointDown() {
elbowStepper.step(-3);
}

//Fuction to move wrist joint Up
void wristJointUp() {
wristStepper.step(3);
}


//Fuction to move wrist joint Down
void wristJointDown() {
wristStepper.step(-3);
}


//Fuction to open Claw Joint
void clawOpen() {
clawStepper.step(3);
}


//Fuction to close Claw joint
void clawClose() {
clawStepper.step(-3);
}

//Function to stop motors from moving
void stopMotor(){
digitalWrite(LEFTMOTORPIN1, LOW);
digitalWrite(LEFTMOTORPIN2, LOW);
digitalWrite(RIGHTMOTORPIN1, LOW);
digitalWrite(RIGHTMOTORPIN2, LOW);
  
}