#include "MathGame.h"
#include "DinoGame.h"

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x25, 16, 2);

Servo player;

int servo = 3;

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

int buzzer = 5;

bool gameRunning = false;

int game = 0;

bool printed = false;

MathGame mathGame;
DinoGame dinoGame;

byte dino[8] = {
  0b00000,
  0b00111,

  0b00111,
  0b10110,
  0b11111,
  0b01010,
  0b01010,
  0b00000
};

byte
  cacti[8] = {
  0b00100,
  0b00101,
  0b10101,
  0b10101,
  0b10111,

  0b11100,
  0b00100,
  0b00000
};

byte bird[8] = {
  0b00000,

  0b00100,
  0b01100,
  0b11110,
  0b00111,
  0b00110,
  0b00100,

  0b00000
};

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

  player.attach(servo);

  lcd1.init();
  lcd1.backlight();
  lcd1.cursor();
  lcd1.createChar(0, dino);
  lcd1.createChar(1, cacti);
  lcd1.createChar(2, bird);

  lcd2.init();
  lcd2.backlight();
  lcd2.cursor();
  lcd2.createChar(0, dino);
  lcd2.createChar(1, cacti);
  lcd2.createChar(2, bird);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!gameRunning) {
    game = 0;

    player.write(70);

    if (!printed) {

      lcd1.clear();
      lcd2.clear();

      lcd1.print("1. Math Racer");
      lcd1.setCursor(0, 1);
      lcd1.print("2. Dino Game");

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
        mathGame.reset();
        dinoGame.reset();
      }
    }
    else submitFlag1 = true;

  }

  else {
    if (game == 1)
      mathGame.runNextIteration(lcd1, lcd2, pot1, button1, back1, submit1, pot2, button2, back2, submit2, flag1, backFlag1, submitFlag1, flag2, backFlag2, submitFlag2, player, gameRunning, buzzer);
    else if (game == 2)
      dinoGame.runNextIteration(lcd1, lcd2, pot1, button1, back1, submit1, pot2, button2, back2, submit2, flag1, backFlag1, submitFlag1, flag2, backFlag2, submitFlag2, player, gameRunning, buzzer);
    printed = false;

    return;
  }

  delay(250);

}
