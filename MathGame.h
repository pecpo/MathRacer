#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>

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

  int threshold = 3;

  int correct1 = 0;
  int correct2 = 0;
  bool solving1 = false, solving2 = false;

  char op[4] = {'+', '-', 'x', '/'};

public:
  void changeCoord(int num, int &coord);
  void displayProblem(LiquidCrystal_I2C &lcd, int &ans, int &coord, int &minPos);
  void parseInput(LiquidCrystal_I2C &p1, LiquidCrystal_I2C &p2, int &ans, int &coord, int &minPos, int &pot, int &button, int &back, int &submit, int &input, bool &flag, bool &backFlag, bool &submitFlag, bool &solving, int &correct, Servo &player, bool &gameRunning);
  void runNextIteration(LiquidCrystal_I2C &lcd1, LiquidCrystal_I2C &lcd2, int &pot1, int &button1, int &back1, int &submit1, int &pot2, int &button2, int &back2, int &submit2, bool &flag1, bool &backFlag1, bool &submitFlag1, bool &flag2, bool &backFlag2, bool &submitFlag2, Servo &player1, Servo &player2, bool &gameRunning);

};