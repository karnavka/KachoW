#include <SparkFun_TB6612.h>
#include "config.h"
#include "motors.h"

static Motor motorL(AIN1, AIN2, PWMA, OFFSET_L, STBY);
static Motor motorR(BIN1, BIN2, PWMB, OFFSET_R, STBY);

void drive(int left, int right) {
  motorL.drive(left);
  motorR.drive(right);
}

void spin(int dir, int speed) {
  drive(dir * speed, -dir * speed);
}
