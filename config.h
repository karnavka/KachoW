
#pragma once
#include <Arduino.h>

// 0 = fight, 1 = test of ensors 2 = test of motors
#define MODE 0

const int AIN1 = 4, AIN2 = 5, PWMA = 9;    // motor A 
const int BIN1 = 6, BIN2 = 7, PWMB = 10;   // motor B 
const int STBY = -1;   // always on cause it is connected straight to battery


const int IR_L = 3;                       
const int IR_R = 2;                        
const int US_L_TRIG = 11, US_L_ECHO = 12;   
const int US_R_TRIG = 13, US_R_ECHO = 8;    
const int LED = -1;    // better to turn it of o can mes up with sensors

// If a wheel spins the wrong way change to -1
const int OFFSET_L = 1;
const int OFFSET_R = 1;


const unsigned long START_WAIT_MS = 5200;  // 0.2  margin CAN BE DELETED????

// if ir show wrong then change it
const int EDGE_LEVEL = LOW;   

const int SEE_CM = 65;                    // ring is 77 cm so maybe will make bigger or smaller
const unsigned long US_TIMEOUT_US = 5000; //how long does it wait for ultraonic sensor can be changes if needed (wo this bound it wait for 1 sec and it is bad because we aint moving)
const unsigned long US_GAP_MS = 20;       // pause between pings so sensors don't hear each other
const unsigned long LOST_MS = 300;        // keep chasing this long after losing sight

const int SEARCH_SPD = 140;   // spinning in place while searching
const int ATTACK_SPD = 255;   // full push
const int STEER_SLOW = 70;    // inner wheel speed when only one sensor sees the opponent
const int REVERSE_SPD = 220;
const int TURN_SPD = 220;
const unsigned long REVERSE_MS = 250;
const unsigned long TURN_MS = 300;
