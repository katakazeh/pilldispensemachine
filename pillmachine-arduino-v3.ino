// test for June event 2023 - v1 

// pill machine v3
// author: Arthur Leung 
// All rights reserved 2023

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos ~50 Hz updates

// Define variables 
int pillnumber = 0;
const byte numChars = 32;
char receivedChars[numChars]; 
char respillarray[4];
const int BUFFER_SIZE = 10;
char buf[BUFFER_SIZE];
String respillarraystring;
// int pillnumbera; 

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
}

// function which the servo moves to get pill out of the system.
void pillout() {

//Positioning note:
//bottom 170 = pill out 
//top 480 = close all hold position
//slot 1 
//bottom = 230 
//top = 390
//slot 2 
//bottom = 315 
//top = 300
//slot 3
//bottom = 393 
//top = 220
//slot 4
//bottom = 475 
//top = 140


  if (pillnumber ==49) {
// test positioning 
//    pwm.setPWM(0, 0, 180); //botttom slot 1 
//    delay(2000);
//    pwm.setPWM(1, 0, 480); //top slot 1
//    delay(2000);

//get slot one pill    
    pwm.setPWM(0, 0, 230); //slot 1 - bottom - final
    delay(1000);
    pwm.setPWM(1, 0, 390); //slot 1 - top - final 
    delay(1000);
    pwm.setPWM(0, 0, 170); //give out pill
    delay(1500);
    pwm.setPWM(1, 0, 480); //close top - final
    delay(1000);
//    pwm.setPWM(0, 0, 500); //close bottom
    delay(1500);
    Serial.println(" end of pill 1 movement");
    } 
  else if (pillnumber ==50) {
//get slot two pill
    Serial.println(" Start of pill 2 movement");
    pwm.setPWM(1, 0, 300); //slot 2 - top - final 
    delay(1000);
    pwm.setPWM(0, 0, 315); //slot 2 - bottom - final
    delay(1000);
    pwm.setPWM(0, 0, 170); //give out pill
    delay(1500);
    pwm.setPWM(1, 0, 480); //close top
    delay(1000);
//    pwm.setPWM(0, 0, 500); //close bottom
//    delay(1500);
    Serial.println(" end of pill 2 movement");
    }
  else if (pillnumber ==51) {
//get slot 3rd pill
    Serial.println(" Start of pill 3 movement");
    pwm.setPWM(1, 0, 220);//slot 3 - top - final 
    delay(1000);
    pwm.setPWM(0, 0, 393); //slot 3 - bottom - final
    delay(1000); 
    pwm.setPWM(0, 0, 170); //give out pill
    delay(1500);
    pwm.setPWM(1, 0, 480); //close top
    delay(1000);
//    pwm.setPWM(0, 0, 500); //close bottom
//    delay(1500);
    Serial.println(" end of pill 3 movement");
    }
else if (pillnumber ==52) {
//get slot 4th pill
    Serial.println(" Start of pill 4 movement");
    pwm.setPWM(1, 0, 140);//slot 4 - top - final 
    delay(1000);
    pwm.setPWM(0, 0, 475); //slot 4 - bottom - final
    delay(1000);
    pwm.setPWM(0, 0, 150); //give out pill
    delay(1500);
    pwm.setPWM(1, 0, 480); //close top
    delay(1000);

//    pwm.setPWM(0, 0, 500); //close bottom
//    delay(1500);
    Serial.println(" end of pill 4 movement");
    }
}
//tring pillnumbera[] = '0';

//main loop
void loop() { 
  // for troubleshooting - command
//  Serial.println(" loop start begin");
  
//set the tube code - before using it. 

  // Collect the pill number from the rpi
  if (Serial.available() > 0) {
//    Serial.readBytesUntil('\n', buf, 4);
      pillnumber = Serial.read();
//      pillnumber = pillnumbera[0];
    }

//  pillnumber=52;

  // print the pill number for troubleshooting purposes
  Serial.println(pillnumber);

  delay(1000);

  // if pillnumber is not 0, then call the pillout function
    if (pillnumber !=0) {
  // trouble shooting 
//  Serial.println("Start the pill machine");

  //pill out function
    pillout();
  
// clean up the pillnumber value
    pillnumber=0;
//    pillnumbera[0] = 0; 
  }
}
