#include <SPI.h>
#include <MFRC522.h>
#include <DigitLedDisplay.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

//Digit led display pins
#define DIN 30
#define LOAD 32
#define CLK 34

#define BUZZPIN A15
#define ALARMPIN A0
#define GRENADEPIN 13

//KEYPINS
// ROWS
#define KEY0 25
#define KEY1 27
#define KEY2 29
#define KEY3 31
// COLUMNS
#define KEY4 33
#define KEY5 35
#define KEY6 37
#define KEY7 39

//Pines de los cables
const int WIRE[4] = {14, 15, 16, 17};
/*#define WIRE1 14
  #define WIRE2 15
  #define WIRE3 16
  #define WIRE4 17*/

//Pines botones
#define RED_BTN 18
#define GREEN_BTN 19

bool bBUZZ = true;
bool bALARM = true;
bool bGRENADE = true;

bool DOMAIN[2] = {false, false};

bool bPASS = true;
String PASS = "123ABC";

bool bWIRE = false;
bool CUTTED_WIRE[4];
int tWIRE[4] = {2, 3, 3, 3};

bool bKEYS = false;

bool ENDGAME = false;
bool WIN = false;
 long RELOJ = 30000;//5 min en centesimas

const byte rowsCount = 4;
const byte columsCount = 4;
char keys[rowsCount][columsCount] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[rowsCount] = { KEY0, KEY1, KEY2, KEY3 };
byte columnPins[columsCount] = { KEY4, KEY5, KEY6, KEY7 };

DigitLedDisplay ld = DigitLedDisplay(DIN, LOAD, CLK);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int RST_PIN = 49;
const int SS_PIN = 53;


MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key nfcKey;

void setupNFC() {
  SPI.begin();
  mfrc522.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    nfcKey.keyByte[i] = 0xFF;
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  ld.setDigitLimit(8);//8 digitos
  setupNFC();

  pinMode(ALARMPIN, OUTPUT);
  pinMode(BUZZPIN, OUTPUT);
  pinMode(WIRE[0], INPUT_PULLUP);
  pinMode(WIRE[1], INPUT_PULLUP);
  pinMode(WIRE[2], INPUT_PULLUP);
  pinMode(WIRE[3], INPUT_PULLUP);
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(GREEN_BTN, INPUT_PULLUP);

}

void setup2() {
  ld.setBright(15); //1-15
  digitalWrite(BUZZPIN, LOW);
  digitalWrite(ALARMPIN, LOW);
  digitalWrite(GRENADEPIN, LOW);
  showTime(RELOJ);
  ENDGAME = false;
  WIN = false;
  for (int i = 0; i < 4; i++)
    CUTTED_WIRE[i] = boolRead(WIRE[i]);
  /*
    CUTTED_WIRE[0] = boolRead(WIRE1);
    CUTTED_WIRE[1] = boolRead(WIRE2);
    CUTTED_WIRE[2] = boolRead(WIRE3);
    CUTTED_WIRE[3] = boolRead(WIRE4);
  */
}

void loop() {
  setup2();
  while (!ENDGAME)
    menu();
}


