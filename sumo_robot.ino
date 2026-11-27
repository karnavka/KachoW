// Strategy: wait 5 s (looking for the opponent while standing still) 
//           spin toward where the opponent was last seen 
//           when seen go to it
//           edge always wins: back up and turn away from the side that saw the edge.
#include "config.h"
#include "motors.h"
#include "sensors.h"

enum State { SEARCH, ATTACK, EDGE_AVOID };
State state = SEARCH;

int edgeTurnDir = +1;

void setLed(bool on) {
  if (LED >= 0) digitalWrite(LED, on ? HIGH : LOW);
}
unsigned long edgeStart = 0;

void setup() {
  Serial.begin(9600);
  sensorsInit();
  motorsInit();
  if (LED >= 0) pinMode(LED, OUTPUT);

#if MODE == 2
  // Motor test: forward 1 s, then spin right 1 s.
  delay(2000);
  drive(120, 120);  delay(1000);
  spin(+1, 120);    delay(1000);
  drive(0, 0);
  while (true) {}
#endif

#if MODE == 0
  unsigned long start = millis();
  while (millis() - start < START_WAIT_MS) {
    updateUltrasonic();
    setLed((millis() / 250) % 2); 
  }
  setLed(LOW);
  state = (seesL() || seesR()) ? ATTACK : SEARCH;
#endif
}

void loop() {
#if MODE == 1
  updateUltrasonic();
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    lastPrint = millis();
    Serial.print("US L: ");  Serial.print(distL());
    Serial.print("  US R: "); Serial.print(distR());
    Serial.print("  | IR L: "); Serial.print(edgeL() ? "EDGE" : "-");
    Serial.print("  IR R: ");   Serial.println(edgeR() ? "EDGE" : "-");
  }
  return;
#endif

  updateUltrasonic();
  bool eL = edgeL(), eR = edgeR();

 
  if ((eL || eR) && state != EDGE_AVOID) {
    state = EDGE_AVOID;
    edgeStart = millis();
    if (eL && !eR)      edgeTurnDir = +1;             // edge on the left -> turn right
    else if (eR && !eL) edgeTurnDir = -1;             // edge on the right -> turn left
    else                edgeTurnDir = lastSeenDir();  // straight at the edge -> toward opponent
  }

  switch (state) {

    case EDGE_AVOID: {
      setLed(LOW); //rn does nothing btw but we can add separate diod
      unsigned long dt = millis() - edgeStart;
      if (dt < REVERSE_MS)                 drive(-REVERSE_SPD, -REVERSE_SPD);
      else if (dt < REVERSE_MS + TURN_MS)  spin(edgeTurnDir, TURN_SPD);
      else if (eL || eR)                   edgeStart = millis();  
      else                                 state = SEARCH;
      break;
    }

    case ATTACK: {
      bool L = seesL(), R = seesR();
      setLed(HIGH);
      if (L && R)  drive(ATTACK_SPD, ATTACK_SPD);   //  push
      else if (L)  drive(STEER_SLOW, ATTACK_SPD);   // left
      else if (R)  drive(ATTACK_SPD, STEER_SLOW);   // ight
      else         state = SEARCH;                  // lost it
      break;
    }

    case SEARCH:
    default: {
      setLed(LOW);
      if (seesL() || seesR()) { state = ATTACK; break; }
      spin(lastSeenDir(), SEARCH_SPD);   // turn toward the side it disappeared on
      break;
    }
  }
}
