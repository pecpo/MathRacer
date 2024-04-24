#include "MathGame.h"

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x25, 16, 2);

Servo player1;
Servo player2;

int servo1 = 3;
int servo2 = 5;

int pot1 = A0;
int button1 = 2;
int back1 = 4;
int submit1 = 7;

int pot2 = A1;
int button2 = 8;
int back2 = 12;
int submit2 = 13;

bool flag1 = true;
bool backFlag1 = true;
bool submitFlag1 = true;

bool flag2 = true;
bool backFlag2 = true;
bool submitFlag2 = true;

bool gameRunning = false;

int game = 0;

bool printed = false;

MathGame mathGame;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(pot1, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(back1, INPUT_PULLUP);
  pinMode(submit1, INPUT_PULLUP);

  pinMode(pot2, INPUT);
  pinMode(button2, INPUT_PULLUP);
  pinMode(back2, INPUT_PULLUP);
  pinMode(submit2, INPUT_PULLUP);

  player1.attach(servo1);
  player2.attach(servo2);

  lcd1.init();
  lcd1.backlight();
  lcd1.cursor();

  lcd2.init();
  lcd2.backlight();
  lcd2.cursor();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!gameRunning) {
    game = 0;

    player1.write(0);
    player2.write(0);

    if (!printed) {

      lcd1.clear();
      lcd2.clear();

      lcd1.print("1. Math Racer");

      printed = true;
    }

    // lcd1.blink();

    int option = map(analogRead(pot1), 0, 1023, 0, 2);
    lcd1.setCursor(0, option);

    int submitVal = digitalRead(submit1);

    if (submitVal == 0) {
      if (submitFlag1) {
        submitFlag1 = false;
        game = option+1;
        gameRunning = true;
      }
    }
    else submitFlag1 = true;

  }

  else {
    if (game == 1)
      mathGame.runNextIteration(lcd1, lcd2, pot1, button1, back1, submit1, pot2, button2, back2, submit2, flag1, backFlag1, submitFlag1, flag2, backFlag2, submitFlag2, player1, player2, gameRunning);
    printed = false;
  }

  delay(250);

}
