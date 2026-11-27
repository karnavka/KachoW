
#pragma once

void sensorsInit();

//(ir) returns true if over the edge
bool edgeL();
bool edgeR();

// one ultrasonic for call
void updateUltrasonic();

// true if opponent was seen by that sensor within the last LOST_MS
bool seesL();
bool seesR();

// Latest raw distances i
int distL();
int distR();

// Side where the opponent was seen last -1 = left, +1 = right
int lastSeenDir();
