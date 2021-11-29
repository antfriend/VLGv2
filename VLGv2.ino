#include <Servo.h> 
#include <SharpIR.h>

#define leftIRPin A0
#define rightIRPin A1
#define model 1080
/* Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
*/
Servo myservo; 
int myservo_pin = 9;
int left_distance_cm;
int right_distance_cm;
SharpIR leftSensor = SharpIR(leftIRPin, model);
SharpIR rightSensor = SharpIR(rightIRPin, model);

void setup() {
  myservo.attach(myservo_pin); 
  set_servo(20);
  delay(500);
}

void loop() {
  left_distance_cm = leftSensor.distance();
  right_distance_cm = rightSensor.distance();
  set_servo(split_the_diff(left_distance_cm, right_distance_cm));
  delay(3000);
  //set_servo(40);
  //delay(10000);
}

int split_the_diff(int lefty, int righty){
  int the_diff = 0;
  if(lefty > righty){
    the_diff = lefty - righty;
    the_diff = 90 + (the_diff/3);
  }else{
    the_diff = righty - lefty;
    the_diff = 90 - (the_diff/3);
  }
  return the_diff;
}

void set_servo(int one_to_180)
{
  int the_int = constrain(one_to_180, 1, 100);
  int reverse_mapped = map(the_int, 1,100,170,1);
  if(myservo.attached() == false)
  {
    myservo.attach(myservo_pin);
  }
  myservo.write(reverse_mapped);
}
