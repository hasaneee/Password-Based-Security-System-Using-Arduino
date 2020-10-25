/*
 * Project Name: Password Based Door Lock System
 * Author: Mahamudul Hasan
 * MCU: Arduino Uno
 * IDE: Arduino IDE
 */

#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#define RELAY_OUTPUT 13

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
  };

byte rowPins[rows] = {8, 9,10, 11};
byte colPins[cols] = {4, 5, 6, 7};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
LiquidCrystal_I2C lcd(0x27, 16, 2);
char customKey;
char inputPass[30];
byte i = 0;
int flag = 0;
char pass[30] = "102030AB";

void setup() {
  //Serial.begin(9600);
  lcd.backlight();
  lcd.init();
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Door Lock");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Develop by");
  lcd.setCursor(1, 1);
  lcd.print("Mahamudul Hasan");
  delay(5000);
  lcd.clear();
  pinMode(RELAY_OUTPUT, OUTPUT);
}
void loop() {
    lcd.setCursor(0, 0); 
    lcd.print("Enter Password");
    digitalWrite(RELAY_OUTPUT, LOW);
    while(flag == 0){
      if(customKey = myKeypad.getKey()){
        if(customKey == '#'){
           flag = 1;
          break;
        }
        //Serial.println(customKey);
        inputPass[i] = customKey;
        lcd.setCursor(i, 1);
        lcd.print(inputPass[i]);
        delay(500);
        lcd.setCursor(i, 1);
        lcd.print("*");
        i++;
      }
  }
  if(flag == 1){
  if(!strcmp(inputPass, pass)){
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Success!");
    lcd.setCursor(0, 1); 
    lcd.print("Door Unlocked");
    digitalWrite(RELAY_OUTPUT, HIGH);
    delay(5000);
    digitalWrite(RELAY_OUTPUT, LOW);
    } else{
      lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Wrong Password");
    lcd.setCursor(0, 1); 
    lcd.print("Try Again...");
    delay(5000);
    }
    lcd.clear();
    flag = 0;
    i = 0;
    //inputPass[0] = '\0';
    memset(inputPass,0,strlen(inputPass));
  }
}
