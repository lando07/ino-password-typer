#include <Keyboard.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define inputClk 4
#define inputDt 5

int counter = 0;
int currStateClk;
int prevStateClk;
LiquidCrystal_I2C lcd(0x27, 20, 4);
String web = "Website: ";
String psswd = "Password: ";
String waiting = "Waiting for Computer";
String hidden = "**********";
String passwords[4][2] = {
  //Website, Passwd
  { "test", "hi" },
  { "test1", "hi1" },
  { "test2", "hi2" },
  { "test3", "hi3" },
};
void setup() {
  //set up pot pins
  //attachInterrupt(0,sendPassword, FALLING);
  pinMode(inputClk, INPUT);
  pinMode(inputDt, INPUT);
  pinMode(3, INPUT);
  //start lcd
  lcd.init();
  lcd.backlight();
  lcd.clear();
  //format display
  lcd.setCursor(0, 0);
  lcd.print(web);
  lcd.setCursor(0, 2);
  lcd.print(psswd);
  prevStateClk = digitalRead(inputClk);
  Keyboard.begin();
}

void loop() {
  currStateClk = digitalRead(inputClk);
  if (currStateClk != prevStateClk) {
    if (digitalRead(inputDt) != currStateClk) {
      counter++;
    } else {
      counter--;
    }
    if (counter > 3) {
      counter = 0;
    } else if (counter < 0) {
      counter = 3;
    }
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print(passwords[counter][0]);
    lcd.setCursor(0, 3);
    lcd.print(passwords[counter][1]);
  }
  if(digitalRead(3) == LOW){
    sendPassword();
    while(digitalRead(3) == LOW);
  }
}

void sendPassword(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending password");
  delay(100);
  Keyboard.print(passwords[counter][1]);
  delay(10);
  lcd.clear();
  lcd.print("Done!");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(web);
  lcd.setCursor(0, 2);
  lcd.print(psswd);
  Keyboard.end();
}