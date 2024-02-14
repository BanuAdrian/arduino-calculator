#include "LiquidCrystal.h"
#include "Keypad.h"

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

uint8_t colPins[COLS] = {9, 8, 7, 6};
uint8_t rowPins[ROWS] = {13, 12, 11, 10};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Calculator");
  lcd.setCursor(9, 1);
  delay(1000);
  lcd.print("digital");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Proiect");
  lcd.setCursor(5, 1);
  delay(1000);
  lcd.print("realizat de");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Banu Constantin");
  lcd.setCursor(9, 1);
  delay(1000);
  lcd.print("Adrian");
  delay(1000);
  lcd.clear();
  lcd.setCursor(14, 0);
  lcd.print("0");
}

String x = "0", y;
boolean secondNumber = false, firstInput = true;
char op;
long res;

int nr_cifre(long a)
{
  int n = 0;
  while (a)
  {
    a /= 10;
    n++;
  }
  return n;
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    if (firstInput == true)
    {
      lcd.clear();
      firstInput = false;
    }
    if (key >= '0' && key <= '9')
    {
      if (secondNumber == false)
      {
        if (x == "0")
          x = "";
        x += key;
        lcd.setCursor(15 - x.length(), 0);
        lcd.print(x);
      }
      else
      {
        if (y == "0")
          y = "";
        y += key;
        lcd.setCursor(15 - y.length(), 1);
        lcd.print(y);
      }
    }
    else if (key == '+' || key == '-' || key == '*' || key == '/')
    {
      lcd.setCursor(15, 0);
      lcd.print(key);
      if (x == "0") {
        lcd.setCursor(14, 0);
        lcd.print("0");
      }
      secondNumber = true;
      op = key;
    }
    else if (key == '=')
    {
      if (op == '+')
        res = x.toInt() + y.toInt();
      else if (op == '-')
        res = x.toInt() - y.toInt();
      else if (op == '*')
        res = x.toInt() * y.toInt();
      else if (op == '/')
        res = x.toInt() / y.toInt();
      else res = x.toInt();
      lcd.clear();
      if (res > 0)
        lcd.setCursor(15 - nr_cifre(res), 0);
      else
        lcd.setCursor(14 - nr_cifre(res), 0);
      lcd.print(res);
      x = String(res);
      y = "";
      op = ' ';
      secondNumber = false;
    }
    else if (key == 'C')
    {
      lcd.clear();
      lcd.setCursor(14, 0);
      lcd.print("0");
      secondNumber = false;
      firstInput = true;
      x = "0";
      y = "";
      res = 0;
      op = ' ';
    }
  }
}
