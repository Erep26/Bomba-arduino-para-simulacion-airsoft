#include <DigitLedDisplay.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define DIN 8
#define LOAD 9
#define CLK 10

#define RESET_PIN 3
DigitLedDisplay ld = DigitLedDisplay(DIN, LOAD, CLK);

//const byte NUM[] = {B11111110,B10110000,B11101101,B11111001,B10110011,B11011011,B11011111,B11110000,B11111111,B11111011};
const byte POINT = B10000000;
const byte NUM[] = {B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,B01111111,B01111011};

String PASS = "123ABC";
String pass = "";

bool ENDGAME = false;
bool WIN = false;
unsigned long RELOJ = 3000;//5 min en centesimas

 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

byte rowPins[rowsCount] = { 0, 1, 2, 3 };
byte columnPins[columsCount] = { 4, 5, 6, 7 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 

LiquidCrystal_I2C lcd(0x27,20,4);

unsigned long TIME = millis();

void setup() {
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  ld.setBright(15); //1-15
  ld.setDigitLimit(8);//8 digitos

  pinMode(RESET_PIN, OUTPUT); 
  //readSequence();
}

void loop() {
  menu();
  game();
  digitalWrite(RESET_PIN, LOW);
}



void showTime(unsigned long t){
  int h = t/360000;
  int m = ((t/100)%3600)/60;
  int s = ((t/100)%3600)%60;
  int cs = t%100;
/*  lcd.clear();
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);
  lcd.print(":");
  lcd.print(cs);*/
  
  ld.write(8, NUM[(int)h/10] );
  ld.write(7, NUM[(int)h%10] + (POINT /** (cs / 10 % 2)*/));
  ld.write(6, NUM[(int)m/10] );
  ld.write(5, NUM[(int)m%10] + (POINT /** (cs / 10 % 2)*/));
  ld.write(4, NUM[(int)s/10] );
  ld.write(3, NUM[(int)s%10] + (POINT /** (cs / 10 % 2)*/));
  ld.write(2, NUM[(int)cs/10] );
  ld.write(1, NUM[(int)cs%10] );
  
  if(millis()/500%2){
    ld.setBright(1); //1-15
  }
  else{
    /*
    ld.write(8, B00000000 );
  ld.write(7, B00000000);
  ld.write(6, B00000000);
  ld.write(5, B00000000);
  ld.write(4, B00000000 );
  ld.write(3, B00000000);
  ld.write(2, B00000000);
  ld.write(1, B00000000);*/
  ld.setBright(15); //1-15
  }
  
}


bool readChar(){
  char key = keypad.getKey();
  if(key){
    switch(key){
      case '#':
        return true;
        break;
      case '*':
        pass = "";
        break;
      default:
        pass += key;
        break;
    }
  }
  return false;
}
