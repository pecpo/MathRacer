#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x25, 16, 2);

Servo player1;
Servo player2;

char op[] = {'+', '-', 'x', '/'};

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

bool solving1 = false, solving2 = false;

int ans1;
int ans2;

int input1 = 0;
int input2 = 0;

int coord1 = 0;
int coord2 = 0;

int minPos1;
int minPos2;

int threshold = 3;

int correct1 = 0;
int correct2 = 0;

bool gameRunning = true;

void changeCoord(int num, int &coord) {
  while(num != 0) {
    coord++;
    num /= 10;
  }
}

void displayProblem(LiquidCrystal_I2C &lcd, int &ans, int &coord, int &minPos) {
  int r = random(4);
  int num1 = random(1, 11);

  int num2;
  if (r == 1) {
    num2 = num1;
    num1 = random(num2, 11);
  }
  if (r == 3) {
    num2 = num1;
    num1 = num2 * random(1, 11);
  }
  else {
    num2 = random(1, 11);
  }

  lcd.clear();
  coord = 0;

  lcd.setCursor(0, 0);

  lcd.print(num1);
  changeCoord(num1, coord);

  lcd.print(" ");
  changeCoord(1, coord);

  lcd.print(op[r]);
  changeCoord(1, coord);

  lcd.print(" ");
  changeCoord(1, coord);

  lcd.print(num2);
  changeCoord(num2, coord);

  lcd.print(" = ");
  changeCoord(100, coord);

  minPos = coord;

  switch(r) {
    case 0:
      ans = num1 + num2;
      break;
    case 1:
      ans = num1 - num2;
      break;
    case 2:
      ans = num1 * num2;
      break;
    case 3:
      ans = num1 / num2;
      break;
  }
}

void parseInput(LiquidCrystal_I2C &p1, LiquidCrystal_I2C &p2, int &ans, int &coord, int &minPos, int &pot, int &button, int &back, int &submit, int &input, int &flag, int &backFlag, int &submitFlag, int &solving, int &correct, Servo &player) {
  if (!solving) {
    displayProblem(p1, ans, coord, minPos);
    solving = true;
  }

  int buttonVal = digitalRead(button);
  int backVal = digitalRead(back);
  int submitVal = digitalRead(submit);

  int num = map(analogRead(pot), 0, 1023, 0, 10);

  p1.setCursor(coord, 0);
  p1.print(num);
  p1.setCursor(coord, 0);

  if (backVal == 0) {
    if (backFlag) {
      if (coord > minPos) {
        p1.print(" ");
        coord--;
        p1.setCursor(coord, 0);
        input /= 10;
      }
      backFlag = false;
    }
  }
  else backFlag = true;

  if (buttonVal == 0) {
    if (flag) {
      coord++;
      input *= 10;
      input += num;

      p1.setCursor(coord, 0);

      flag = false;
    }
  }
  else flag = true;

  if (submitVal == 0) {
    if (submitFlag) {
      solving = false;
      input *= 10;
      input += num;
      p1.setCursor(0,1);
      if (input == ans) {
        p1.print("Correct!");
        correct++;
        if (correct > threshold) {
          player.write(180);
          p1.clear();
          p1.print("WINNER!");
          p2.clear();
          p2.print("LOSER!");
          gameRunning = false;
        }
      }
      else {
        p1.print("Wrong!");
      }
      input = 0;
      submitFlag = false;
    }
  }
  else {
    submitFlag = true;
  }
}

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

  player1.write(0);
  player2.write(0);

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
    delay(1000);
    return;
  }

  if (!solving1) {
    ans1=displayProblem(lcd1, ans1, coord1, minPos1);
    solving1 = true;
  }

  if (!solving2) {
    ans2=displayProblem(lcd2, ans2, coord2, minPos2);
    solving2 = true;
  }

  int buttonVal1 = digitalRead(button1);
  int backVal1 = digitalRead(back1);
  int submitVal1 = digitalRead(submit1);

  int num1 = map(analogRead(pot1), 0, 1023, 0, 10);

  int buttonVal2 = digitalRead(button2);
  int backVal2 = digitalRead(back2);
  int submitVal2 = digitalRead(submit2);

  int num2 = map(analogRead(pot2), 0, 1023, 0, 10);

  // lcd1.blink();

  // Serial.println(backVal1);

  lcd1.print(num1);
  lcd1.setCursor(coord1, 0);

  lcd2.print(num2);
  lcd2.setCursor(coord2, 0);

  if (backVal1 == 0) {
    if (backFlag1) {
      if (coord1 > minPos1) {
        lcd1.print(" ");
        coord1--;
        lcd1.setCursor(coord1, 0);
        input1 /= 10;
      }
      backFlag1 = false;
    }
  }
  else backFlag1 = true;

  if (buttonVal1 == 0) {
    if (flag1) {
      coord1++;
      input1 *= 10;
      input1 += num1;

      lcd1.setCursor(coord1, 0);

      flag1 = false;
    }
  }
  else flag1 = true;

  if (submitVal1 == 0) {
    if (submitFlag1) {
      solving1 = false;
      input1 *= 10;
      input1 += num1;
      lcd1.setCursor(0,1);
      if (input1 == ans1) {
        Serial.println("1. Correct");
        lcd1.print("Correct!");
        correct1++;
        if (correct1 > threshold) {
          player1.write(180);
          lcd1.clear();
          lcd1.print("WINNER!");
          lcd2.clear();
          lcd2.print("LOSER!");
          gameRunning = false;
        }
      }
      else {
        Serial.println("1. Wrong!");
        lcd1.print("Wrong!");
        Serial.println(input1+" "+ans1);
      }
      input1 = 0;
      submitFlag1 = false;
    }
  }
  else {
    submitFlag1 = true;
  }


  if (backVal2 == 0) {
    if (backFlag2) {
      if (coord2 > minPos2) {
        lcd2.print(" ");
        coord2--;
        lcd2.setCursor(coord2, 0);
        input2 /= 10;
      }
      backFlag2 = false;
    }
  }
  else backFlag2 = true;

  if (buttonVal2 == 0) {
    if (flag2) {
      coord2++;
      input2 *= 10;
      input2 += num2;

      lcd2.setCursor(coord2, 0);

      flag2 = false;
    }
  }
  else flag2 = true;

  if (submitVal2 == 0) {
    if (submitFlag2) {
      solving2 = false;
      input2 *= 10;
      input2 += num2; 
      lcd2.setCursor(0,1);
      if (input2 == ans2) {
        Serial.println("2. Correct");
        lcd2.print("Correct!");
        correct2++;
        if (correct2 > threshold) {
          player2.write(180);
          lcd2.clear();
          lcd2.print("WINNER!");
          lcd1.clear();
          lcd1.print("LOSER!");
          gameRunning = false;
        }
      }
      else {
        Serial.println("2. Wrong!");
        lcd2.print("Wrong!");
      }
      input2 = 0;
      submitFlag2 = false;
    }
  }
  else {
    submitFlag2 = true;
  }

  delay(250);

}
