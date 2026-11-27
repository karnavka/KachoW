#pragma once

void sensorsInit();

bool edgeL();
bool edgeR();

// call one of ultraonics per call
void updateUltrasonic();

// true if opponent was seen by that sensor within the last LOST_MS
bool seesL();
bool seesR();

// Latest raw distances in cm 
int distL();
int distR();

// -1 left 1 right
int lastSeenDir();
