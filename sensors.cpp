#include "config.h"
#include "sensors.h"

static int dL = 999, dR = 999;
static unsigned long lastSeenLms = 0, lastSeenRms = 0;
static bool everL = false, everR = false;
static int lastDir = +1;

void sensorsInit() {
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(US_L_TRIG, OUTPUT); pinMode(US_L_ECHO, INPUT);
  pinMode(US_R_TRIG, OUTPUT); pinMode(US_R_ECHO, INPUT);
  digitalWrite(US_L_TRIG, LOW);
  digitalWrite(US_R_TRIG, LOW);
}

bool edgeL() { return digitalRead(IR_L) == EDGE_LEVEL; }
bool edgeR() { return digitalRead(IR_R) == EDGE_LEVEL; }

static int pingCm(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  unsigned long dur = pulseIn(echo, HIGH, US_TIMEOUT_US);
  if (dur == 0) return 999;             
  return (int)(dur * 0.0343 / 2.0);
}

void updateUltrasonic() {
  static unsigned long lastPing = 0;
  static bool doLeft = true;
  if (millis() - lastPing < US_GAP_MS) return;

  if (doLeft) {
    dL = pingCm(US_L_TRIG, US_L_ECHO);
    if (dL <= SEE_CM) { lastSeenLms = millis(); everL = true; lastDir = -1; }
  } else {
    dR = pingCm(US_R_TRIG, US_R_ECHO);
    if (dR <= SEE_CM) { lastSeenRms = millis(); everR = true; lastDir = +1; }
  }
  doLeft = !doLeft;
  lastPing = millis();
}

bool seesL() { return everL && millis() - lastSeenLms < LOST_MS; }
bool seesR() { return everR && millis() - lastSeenRms < LOST_MS; }
int distL() { return dL; }
int distR() { return dR; }
int lastSeenDir() { return lastDir; }
