#include <LiquidCrystal.h>

/*
 * If you don't want to change anything you need to wire up your LCD like in the LCD starter example.
 * You may also connect 2 pushbuttons and connect them to pin 6 and 9. Or you choose pins yourself.
 * 
 * Inputs characters of the alphabet that you can cycle through to the screen and prints them
 * on the screen if you hit the button thats connected to the confirmPin (In my case it's pin 9)
 * The input stops after both rows are full.
 * 
 * by Felix Naumann (failex234)
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int nextPin = 6;
const int confirmPin = 9;

int currchars = 0;
int currrow2chars = 0;
int currindex = 0;
int rows = 1;
char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', ' '};
char row1[16];
char row2[16];

boolean isEnabled = true;
void setup() {
  lcd.begin(16, 2);

  //Set both Pins as Input
  pinMode(nextPin, INPUT);
  pinMode(confirmPin, INPUT);
}

void loop() {
  //Show a splash screen for approx. 5 seconds
  if (millis() > 5000) {
    if (currrow2chars == 16) isEnabled = false;
    if (currchars == 16) rows = 2;
    //Go to next character and return back to A if we're at 27
    if (digitalRead(nextPin) == HIGH && isEnabled) {
      currindex++;
      if (currindex == 27) currindex = 0;
      delay(120);
    }

    //Add currently selected character to the array
    if (digitalRead(confirmPin) == HIGH && isEnabled) {
      if (rows == 1) {
      row1[currchars] = alphabet[currindex];
      currindex = 0;
      currchars++;
      } else {
        row2[currrow2chars] = alphabet[currindex];
        currindex = 0;
        currchars++;
        currrow2chars++;
      }
      delay(120);
    }
    if (currchars >= 1) {
      if (rows != 1) {
      lcd.print(row1);
      lcd.setCursor(0,1);
      if (currchars > 16) {
      lcd.print(row2);
      }
      lcd.print(alphabet[currindex]);
      } else {
      lcd.print(row1);
      lcd.print(alphabet[currindex]);
      }
    } else {
      lcd.print(alphabet[currindex]);
    }
    delay(60);
    lcd.clear();
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Arduino UNO R3");
    lcd.setCursor(0,1);
    lcd.print("starting up...");
    delay(50);
  }
}
