#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>
#include "pitches.h"

class DinoGame {
  private:
    bool jumped1 = false;
    bool jumped2 = false;

    int gameSpeed1;
    int gameSpeed2;

    int waited1 = 0;
    int waited2 = 0;

    byte state1[16] = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
    byte state2[16] = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128};

    int melody[32] = {
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_C3,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[32] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
};

int length = 32;

int deathMelody[24] = {
  NOTE_A4, NOTE_REST, NOTE_GS4, NOTE_REST,
  NOTE_G4, NOTE_REST, NOTE_FS4, NOTE_REST,
  NOTE_F4, NOTE_REST, NOTE_E4, NOTE_REST,
  NOTE_D4, NOTE_REST, NOTE_CS4, NOTE_REST,
  NOTE_C4, NOTE_REST, NOTE_B3, NOTE_REST,
  NOTE_AS3, NOTE_REST, NOTE_A3, NOTE_REST,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int deathNoteDurations[24] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
};

int deathLength = 24;

  public:
    bool isCacti(byte val);
    bool isBird(byte val);
    void parseInput(LiquidCrystal_I2C &lcd, LiquidCrystal_I2C &p2, bool &jumped, int &pot, int &button, int &back, int &submit, bool &flag, bool &backFlag, bool &submitFlag, byte state[16], bool &gameRunning, Servo &player, bool left, int &buzzer);
    void runNextIteration(LiquidCrystal_I2C &lcd1, LiquidCrystal_I2C &lcd2, int &pot1, int &button1, int &back1, int &submit1, int &pot2, int &button2, int &back2, int &submit2, bool &flag1, bool &backFlag1, bool &submitFlag1, bool &flag2, bool &backFlag2, bool &submitFlag2, Servo &player, bool &gameRunning, int &buzzer);
    void reset();
};