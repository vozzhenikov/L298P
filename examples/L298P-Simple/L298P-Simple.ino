#include <L298P.h>

#define RIGHT_MOTOR_PWM       10
#define RIGHT_MOTOR_DIRECTION 12
#define LEFT_MOTOR_PWM        11
#define LEFT_MOTOR_DIRECTION  13

L298P motorRight(RIGHT_MOTOR_DIRECTION, RIGHT_MOTOR_PWM, true); // create motor #1
L298P motorLeft(LEFT_MOTOR_DIRECTION, LEFT_MOTOR_PWM);      	// create motor #2

void setup() {
  motorRight.stop();
  motorLeft.stop();
  
  motorRight.setSpeed(255);
  motorLeft.setSpeed(255);
}

void loop() {
  motorRight.forward();      
  motorLeft.forward();
  
  delay(5000);
  
  motorRight.backward();      
  motorLeft.backward();

  delay(5000);
}