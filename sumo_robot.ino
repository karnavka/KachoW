
//           wait 5 s vut sensors are on
//           spin toward where the opponent was last seen (legt right or both)
//           when seen, charge and steer toward it 
//           if edge is seen back up

#include "config.h"
#include "motors.h"
#include "sensors.h"

enum State { SEARCH, ATTACK, EDGE_AVOID };
State state = SEARCH;

int edgeTurnDir = +1;
unsigned long edgeStart = 0;

void setup() {
  Serial.begin(9600);
  sensorsInit();
  pinMode(LED, OUTPUT);
  pinMode(STBY, OUTPUT);
  drive(0, 0);

#if MODE == 2
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
    digitalWrite(LED, (millis() / 250) % 2);  
  }
  digitalWrite(LED, LOW);
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
    if (eL && !eR)      edgeTurnDir = +1;             
    else if (eR && !eL) edgeTurnDir = -1;            
    else                edgeTurnDir = lastSeenDir();  
  }

  switch (state) {

    case EDGE_AVOID: {
      digitalWrite(LED, LOW);
      unsigned long dt = millis() - edgeStart;
      if (dt < REVERSE_MS)                 drive(-REVERSE_SPD, -REVERSE_SPD);
      else if (dt < REVERSE_MS + TURN_MS)  spin(edgeTurnDir, TURN_SPD);
      else if (eL || eR)                   edgeStart = millis();   
      else                                 state = SEARCH;
      break;
    }

    case ATTACK: {
      bool L = seesL(), R = seesR();
      digitalWrite(LED, HIGH);
      if (L && R)  drive(ATTACK_SPD, ATTACK_SPD);   
      else if (L)  drive(STEER_SLOW, ATTACK_SPD);  
      else if (R)  drive(ATTACK_SPD, STEER_SLOW);  
      else         state = SEARCH;                
      break;
    }

    case SEARCH:
    default: {
      digitalWrite(LED, LOW);
      if (seesL() || seesR()) { state = ATTACK; break; }
      spin(lastSeenDir(), SEARCH_SPD);   
      break;
    }
  }
}
