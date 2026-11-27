#include "config.h"
#include "motors.h"

//   IN1/IN2 direction (HIGH/LOW forward, LOW/HIGH backward, LOW/LOW stop)
static void setMotor(int in1, int in2, int pwm, int offset, int speed) {
  speed = constrain(speed * offset, -255, 255);  
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  analogWrite(pwm, speed);
}

void motorsInit() {
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT); pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);
  if (STBY >= 0) {           
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH); 
  }
  drive(0, 0);
}

void drive(int left, int right) {
  setMotor(AIN1, AIN2, PWMA, OFFSET_L, left);
  setMotor(BIN1, BIN2, PWMB, OFFSET_R, right);
}

void spin(int dir, int speed) {
  drive(dir * speed, -dir * speed);
}
