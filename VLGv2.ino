#include <Arduino.h>
#include <SharpIR.h>
#include "ServoEasing.hpp"

#include "PinDefinitionsAndMore.h"

ServoEasing Servo1;

#define START_DEGREE_VALUE 90

#define leftIRPin A0
#define rightIRPin A1
#define model 1080
/* Sharp Sensor Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
*/
//Servo myservo; 
int myservo_pin = 9;
int left_distance_cm;
int right_distance_cm;
SharpIR leftSensor = SharpIR(leftIRPin, model);
SharpIR rightSensor = SharpIR(rightIRPin, model);

void setup() {
  Serial.begin(9600);

  if (Servo1.attach(SERVO1_PIN, START_DEGREE_VALUE) == INVALID_SERVO) {
      Serial.println(F("Error attaching servo"));
  }
  delay(500);
  Servo1.easeTo(90, 20);
  
  delay(1000);
  Servo1.setSpeed(40);
  Servo1.setEasingType(EASE_CUBIC_IN_OUT);
  Servo1.easeTo(180);
  delay(500);
}

void loop() {
  //servo.tick();
  left_distance_cm = constrain(leftSensor.distance(), 1, 90);
  right_distance_cm = constrain(rightSensor.distance(), 1, 90);
  set_servo(split_the_diff(left_distance_cm, right_distance_cm));
  Serial. println(String(left_distance_cm)  +  " "  +  String(right_distance_cm)/* + " " + String(state)*/);
  
  delay(100);
}

int split_the_diff(int lefty, int righty){
  int the_diff = 0;
  if(lefty < righty){
    the_diff = lefty;
  }else{
    the_diff = map(righty, 1,180,180,1);
  }
  return the_diff;
}

void set_servo(int one_to_180)
{
  //int reverse_mapped = map(one_to_180, 1,180,180,1);
  Serial. println(String(one_to_180));
  Servo1.easeTo(one_to_180);
}

///*
// * User defined combined movement
// */
//float EaseQuadraticInQuarticOut(float aPercentageOfCompletion) {
//    if (aPercentageOfCompletion <= 0.5) {
//        // Quadratic IN - output from 0.0 to 0.5
//        return (2 * QuadraticEaseIn(aPercentageOfCompletion));
//    } else {
//        // Quartic OUT - output from 0.5 to 1.0
//        return (1.0 - (8 * QuarticEaseIn(1.0 - aPercentageOfCompletion)));
//    }
//}
