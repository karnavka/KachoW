// pins
#pragma once
#include <Arduino.h>


// 0 = fight, 1 = print sensors to Serial (motors off), 2 = motor direction test
#define MODE 0

//THIS NAMES ARE FROM DOCUMENTATION I DIDNT MAKE THEM UP 

//IN are direction
//PMW speed
//STBY common for bith roters
//A is left, B is right
const int AIN1 = 2, AIN2 = 3, PWMA = 5;   // left motor
const int BIN1 = 4, BIN2 = 7, PWMB = 6;   // right motor
const int STBY = 12;

const int IR_L = 8;                        // left ir
const int IR_R = A1;                       // fright eir
const int US_L_TRIG = 9,  US_L_ECHO = 10;  // left ultrasonic
const int US_R_TRIG = 11, US_R_ECHO = A0;  // right ultrasonic
const int LED = 13;

const int OFFSET_L = 1;
const int OFFSET_R = 1;

const unsigned long START_WAIT_MS = 5200;  

const int EDGE_LEVEL = LOW;   

const int SEE_CM = 65;                    // ring is 77 cm so maybe will make bigger or smaller
const unsigned long US_TIMEOUT_US = 5000; //how long does it wait for ultraonic sensor can be changes if needed (wo this bound it wait for 1 sec and it is bad because we aint moving)
const unsigned long US_GAP_MS = 20;       // pause between pings so sensors don't hear each other
const unsigned long LOST_MS = 300;        // keep chasing this long after losing sight

const int SEARCH_SPD = 140;   // spinning in place while searching
const int ATTACK_SPD = 255;   // full push
const int STEER_SLOW = 70;    // the smaller thi number the teeper the rotation
const int REVERSE_SPD = 220;
const int TURN_SPD = 220;
const unsigned long REVERSE_MS = 250;
const unsigned long TURN_MS = 300;
