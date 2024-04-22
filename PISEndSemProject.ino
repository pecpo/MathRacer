#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);

char op[] = {'+', '-', 'x', '/'};

int pot1 = A0;
int button1 = 2;
int back1 = 4;
int submit1 = 7;

bool flag1 = true;
bool backFlag1 = true;
bool submitFlag1 = true;

bool solving1 = false, solving2 = false;

int ans1;
int ans2;

int input1 = 0;

int coord1 = 0;
int minPos1;

void changeCoord1(int num) {
  while(num != 0) {
    coord1++;
    num /= 10;
  }
}

void displayProblem(LiquidCrystal_I2C lcd, int &ans) {
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
  coord1 = 0;

  lcd.setCursor(0, 0);

  lcd.print(num1);
  changeCoord1(num1);

  lcd.print(" ");
  changeCoord1(1);

  lcd.print(op[r]);
  changeCoord1(1);

  lcd.print(" ");
  changeCoord1(1);

  lcd.print(num2);
  changeCoord1(num2);

  lcd.print(" = ");
  changeCoord1(100);

  minPos1 = coord1;

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

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(pot1, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(back1, INPUT_PULLUP);
  pinMode(submit1, INPUT_PULLUP);

  lcd1.init();
  lcd1.backlight();
  lcd1.cursor();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!solving1) {
    displayProblem(lcd1, ans1);
    solving1 = true;
  }

  int r = analogRead(pot1);
  int val = map(r, 0, 1023, 0, 9);

  int buttonVal1 = digitalRead(button1);
  int backVal1 = digitalRead(back1);
  int submitVal1 = digitalRead(submit1);

  int num1 = map(analogRead(pot1), 0, 1023, 0, 10);

  // lcd1.blink();

  // Serial.println(backVal1);

  lcd1.print(num1);
  lcd1.setCursor(coord1, 0);

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
      if (input1 == ans1) {
        Serial.println("Correct");
      }
      else {
        Serial.println("Wrong!");
      }
      input1 = 0;
      submitFlag1 = false;
    }
  }
  else {
    submitFlag1 = true;
  }

  delay(250);

}
