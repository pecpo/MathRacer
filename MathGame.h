#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>
#include "pitches.h"

class MathGame {
private:
  int ans1;
  int ans2;

  int input1 = 0;
  int input2 = 0;

  int coord1 = 0;
  int coord2 = 0;

  int minPos1;
  int minPos2;

  int threshold = 5;

  int correct1 = 0;
  int correct2 = 0;
  bool solving1 = false, solving2 = false;

  char op[4] = {'+', '-', 'x', '/'};

 int melodyLength = 29;

 int currentPlaying = 0;


  int melody[29] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5,
  NOTE_G4, NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_D5,
  NOTE_A4, NOTE_F4, NOTE_D4,
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E5,
  NOTE_B4, NOTE_G4, NOTE_E4,
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[29] = {
  4, 4, 4, 4,
  4, 4, 2,
  4, 4, 4, 4,
  4, 4, 2,
  4, 4, 4, 4,
  4, 4, 2,
  4, 8, 8, 4, 4, 4, 4, 4
};

int deathMelody[12] = {
  NOTE_C5, NOTE_E5, NOTE_G5,
  NOTE_C5, NOTE_E5, NOTE_G5,
  NOTE_C5, NOTE_E5, NOTE_G5,
  NOTE_C5, NOTE_E5, NOTE_G5,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int deathNoteDurations[12] = {
  4, 4, 4,
  4, 4, 4,
  4, 4, 4,
  4, 4, 4,
};

int deathLength = 12;

public:
  void changeCoord(int num, int &coord);
  void displayProblem(LiquidCrystal_I2C &lcd, int &ans, int &coord, int &minPos);
  void parseInput(LiquidCrystal_I2C &p1, LiquidCrystal_I2C &p2, int &ans, int &coord, int &minPos, int &pot, int &button, int &back, int &submit, int &input, bool &flag, bool &backFlag, bool &submitFlag, bool &solving, int &correct, Servo &player, bool &gameRunning, bool left, int &buzzer);
  void runNextIteration(LiquidCrystal_I2C &lcd1, LiquidCrystal_I2C &lcd2, int &pot1, int &button1, int &back1, int &submit1, int &pot2, int &button2, int &back2, int &submit2, bool &flag1, bool &backFlag1, bool &submitFlag1, bool &flag2, bool &backFlag2, bool &submitFlag2, Servo &player, bool &gameRunning, int &buzzer);
  void playDeath(int &buzzer);
  void reset();
};