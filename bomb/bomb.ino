#include <SPI.h>
#include <MFRC522.h>
#include <DigitLedDisplay.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

//I2C pins
#define DIN 11
#define LOAD 10
#define CLK 9

#define BUZZPIN 2
#define ALARMPIN 12

//KEYPINS
// ROWS
#define KEY0 A8
#define KEY1 A9
#define KEY2 A10
#define KEY3 A11
// COLUMNS
#define KEY4 A12
#define KEY5 A13
#define KEY6 A14
#define KEY7 A15

//Pines de los cables
#define WIRE1 1
#define WIRE2 2
#define WIRE3 3
#define WIRE4 4

DigitLedDisplay ld = DigitLedDisplay(DIN, LOAD, CLK);

//const byte NUM[] = {B11111110,B10110000,B11101101,B11111001,B10110011,B11011011,B11011111,B11110000,B11111111,B11111011};
const byte POINT = B10000000;
const byte NUM[] = {B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,B01111111,B01111011};

bool bPASS = true;
String PASS = "123ABC";

bool bWIRE = false;
int tWIRE1 = 2;
int tWIRE2 = 3;
int tWIRE3 = 3;
int tWIRE4 = 3;

bool ENDGAME = false;
bool WIN = false;
unsigned long RELOJ = 30000;//5 min en centesimas
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

byte rowPins[rowsCount] = { KEY0, KEY1, KEY2, KEY3 };
byte columnPins[columsCount] = { KEY4, KEY5, KEY6, KEY7 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 

LiquidCrystal_I2C lcd(0x27,20,4);

unsigned long TIME = millis();

void setup() {
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  ld.setDigitLimit(8);//8 digitos

  pinMode(BUZZPIN, OUTPUT);
  pinMode(WIRE1, INPUT);
  pinMode(WIRE2, INPUT);
  pinMode(WIRE3, INPUT);
  pinMode(WIRE4, INPUT);
  
  //readSequence();
}

void setup2(){
  ld.setBright(15); //1-15
  digitalWrite(BUZZPIN, LOW);
  showTime(RELOJ);
  ENDGAME = false;
  WIN =false;
}

void loop() {
  setup2();
  while(!ENDGAME)
    menu();
}
