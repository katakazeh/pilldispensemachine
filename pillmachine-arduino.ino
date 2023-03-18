// pill machine v2 final
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

  if (pillnumber == 1) {
//get slot one pill
    Serial.println(" Start of pill 1 movement ");
    pwm.setPWM(0, 0, 200); //slot 1 - bottom - final
    delay(1000);
    pwm.setPWM(1, 0, 400); //slot 1 - top - final 
    delay(300);
    pwm.setPWM(1, 0, 500); //close top - final
    delay(300);
    pwm.setPWM(0, 0, 145); //give out pill
    pwm.setPWM(0, 0, 150); //give out pill
    delay(1500);
    pwm.setPWM(0, 0, 500); //close bottom
    delay(1500);
    Serial.println(" end of pill 1 movement");
    } 
  else if (pillnumber ==2) {
//get slot two pill
    Serial.println(" Start of pill 2 movement");
    pwm.setPWM(0, 0, 290); //slot 2 - bottom - final
    delay(1000);
    pwm.setPWM(1, 0, 312); //slot 2 - top - final 
    delay(300);
    pwm.setPWM(1, 0, 500); //close top
    delay(300);
    pwm.setPWM(0, 0, 145); //give out pill
    pwm.setPWM(0, 0, 150); //give out pill
    delay(1500);
    pwm.setPWM(0, 0, 500); //close bottom
    delay(1500);
    Serial.println(" end of pill 2 movement");
    }
  else if (pillnumber ==3) {
//get slot 3rd pill
    Serial.println(" Start of pill 3 movement");
    pwm.setPWM(0, 0, 370); //slot 3 - bottom - final
    delay(1000);
    pwm.setPWM(1, 0, 240);//slot 3 - top - final 
    delay(1000);
    pwm.setPWM(1, 0, 500); //close top
    delay(400);
    pwm.setPWM(0, 0, 145); //give out pill
    pwm.setPWM(0, 0, 150); //give out pill
    delay(1500);
    pwm.setPWM(0, 0, 500); //close bottom
    delay(1500);
    Serial.println(" end of pill 3 movement");
    }
else if (pillnumber ==4) {
//get slot 4th pill
    Serial.println(" Start of pill 4 movement");
    pwm.setPWM(0, 0, 450); //slot 4 - bottom - final
    delay(1000);
    pwm.setPWM(1, 0, 150);//slot 4 - top - final 
    delay(1000);
    pwm.setPWM(1, 0, 500); //close top
    delay(400);
    pwm.setPWM(0, 0, 145); //give out pill
    pwm.setPWM(0, 0, 150); //give out pill
    delay(1500);
    pwm.setPWM(0, 0, 500); //close bottom
    delay(1500);
    Serial.println(" end of pill 4 movement");
    }
}

//main loop
void loop() { 
  // for troubleshooting - command
  Serial.println(" loop start begin");

  // Collect the pill number from the rpi
  if (Serial.available() > 0) {
    pillnumber = Serial.readBytesUntil('\n', buf, 1);
    }

  // print the pill number for troubleshooting purposes
  Serial.println(pillnumber);

  delay(2000);

  // if pillnumber is not 0, then call the pillout function
    if (pillnumber !=0) {
  // trouble shooting 
  Serial.println("Start the pill machine");

  //pill out function
    pillout();
  
// clean up the pillnumber value
    pillnumber =0; 
  }
}
