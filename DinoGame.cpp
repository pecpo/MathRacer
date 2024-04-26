#include "DinoGame.h"

bool DinoGame::isCacti(byte val) {
  if (val <= 64) {
    return true;
  }

  return false;
}

bool DinoGame::isBird(byte val) {
  if (val >= 192) {
    return true;
  }
  
  return false;
}

void DinoGame::playDeath(int &buzzer) {
  for (int thisNote = 0; thisNote < deathLength; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / deathNoteDurations[thisNote];

    tone(buzzer, deathMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(buzzer);

  }
}

void DinoGame::parseInput(LiquidCrystal_I2C &lcd, LiquidCrystal_I2C &p2, bool &jumped, int &pot, int &button, int &back, int &submit, bool &flag, bool &backFlag, bool &submitFlag, byte state[16], bool &gameRunning, Servo &player, bool left, int &buzzer, int &score) {
  
  int submitVal = digitalRead(submit);

  lcd.clear();
  
  if (submitVal == 0) {
    if (submitFlag) {
      submitFlag = false;
      jumped = true;
    }
  } else {
    submitFlag = true;
    jumped = false;
  }

  if (isCacti(state[0])) {
    if (!jumped) {
      gameRunning = false;
    }
  }
  else if (isBird(state[0])) {
    if (jumped) {
      gameRunning = false;
    }
  }

  if (score > threshold) {
    gameRunning = false;
    lcd.clear();
    p2.clear();

    lcd.print("WINNER!");
    p2.print("LOSER!");

    if (left) {
      player.write(140);
    }
    else {
      player.write(0);
    }

    delay(1000);

    return;
  }

  if (!gameRunning) {
    lcd.clear();
    p2.clear();

    lcd.print("LOSER!");
    p2.print("WINNER!");

    if (left) {
      player.write(0);
    }
    else {
      player.write(140);
    }

    delay(1000);

    return;
  }

  // for (int i = 0; i < 16; i++) {
  //   Serial.print(state1[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();

  for (int i = 0; i < 16; i++) {
    if (isCacti(state[i])) {
      lcd.setCursor(i, 1);
      lcd.write(1);
    }
    else if (isBird(state[i])) {
      lcd.setCursor(i, 0);
      lcd.write(2);
    }
  }

  if (jumped) {
    lcd.setCursor(0, 0);
  }
  else {
    lcd.setCursor(0, 1);
  }

  lcd.write(0);

  for (int i = 0; i < 15; i++) {
    state[i] = state[i+1];
  }

  state[15] = random(0, 256);

  if ((isBird(state[14])) && (isCacti(state[15]))) {
    state[15] = 128;
  }
  else if ((isCacti(state[14])) && (isBird(state[15]))) {
    state[15] = 128;
  }
}

void DinoGame::runNextIteration(LiquidCrystal_I2C &lcd1, LiquidCrystal_I2C &lcd2, int &pot1, int &button1, int &back1, int &submit1, int &pot2, int &button2, int &back2, int &submit2, bool &flag1, bool &backFlag1, bool &submitFlag1, bool &flag2, bool &backFlag2, bool &submitFlag2, Servo &player, bool &gameRunning, int &buzzer) {
  if (!gameRunning) {
    playDeath(buzzer);
    return;
  }

  gameSpeed1 = 1000 - map(analogRead(pot1), 0, 1023, 0, 1000);
  gameSpeed2 = 1000 - map(analogRead(pot2), 0, 1023, 0, 1000);

  if (waited1 >= gameSpeed1) {
    score1++;
    parseInput(lcd1, lcd2, jumped1, pot1, button1, back1, submit1, flag1, backFlag1, submitFlag1, state1, gameRunning, player, true, buzzer, score1);
    if (!gameRunning) {
      playDeath(buzzer);
      return;
    }
    waited1 = 0;
  }
  if (waited2 >= gameSpeed2) {
    score2++;
    parseInput(lcd2, lcd1, jumped2, pot2, button2, back2, submit2, flag2, backFlag2, submitFlag2, state2, gameRunning, player, false, buzzer, score2);
    if (!gameRunning) {
      playDeath(buzzer);
      return;
    }
    waited2 = 0;
  }

  int k = abs(min(gameSpeed1 - waited1, gameSpeed2 - waited2));

  delay(k);

  waited1 += k;
  waited2 += k;
}

void DinoGame::reset() {
  jumped1 = false;
  jumped2 = false;

  waited1 = 0;
  waited2 = 0;

  score1 = 0;
  score2 = 0;

  for (int i = 0; i < 16; i++) {
    state1[i] = 128;
    state2[i] = 128;
  }
}