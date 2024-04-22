#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);

char op[] = {'+', '-', 'x', '/'};

int pot1 = A0;
int button1 = 2;
bool flag1 = true;

int ans1;
int ans2;

void displayProblem(LiquidCrystal_I2C lcd, int &ans) {
  int r = random(4);
  int num1 = random(1, 11);

  int num2;
  if (r == 1) {
    num2 = random(num1, 11);
  }
  if (r == 3) {
    num2 = num1;
    num1 = num2 * random(1, 11);
  }
  else {
    num2 = random(1, 11);
  }

  lcd.clear();

  lcd.setCursor(0, 0);
  
  lcd.print(num1);
  lcd.print(" ");
  lcd.print(op[r]);
  lcd.print(" ");
  lcd.print(num2);
  lcd.print(" = ");

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

  lcd1.init();
  lcd1.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:

  // int r = analogRead(pot1);
  // int val = map(r, 0, 1023, 0, 9);
  // Serial.println(val);

  // int k = digitalRead(button1);

  //   if (k == 0) {
  //     if (flag1) {
  //     Serial.print(map(analogRead(pot1), 0, 1023, 0, 9));
  //     flag1 = false;
  //     }
  //   }
  //   else flag1 = true;

  displayProblem(lcd1, ans1);

  lcd1.print(ans1);

  delay(5000);

}
