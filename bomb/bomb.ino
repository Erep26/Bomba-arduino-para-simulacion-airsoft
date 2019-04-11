#include <SparkFun_MMA8452Q.h>
#include <SPI.h>
#include <MFRC522.h>
#include <DigitLedDisplay.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

//#include "lang.h"

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

//Pines botones
#define RED_BTN 18
#define GREEN_BTN 19

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

#define RST_PIN 49
#define SS_PIN 53


MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key nfcKey;

MMA8452Q accel;

//----------------------------------TEXTOS--------------------------------------------
const PROGMEM String MENU_PRINCIPAL[] = { "Menu", "1.-Iniciar juego", "2.-Configuracion", ""};
const PROGMEM String MENU_JUEGO[] = {"1.-Counterstrike", "2.-Asalto", "3.-Dominacion", "4.-Explosivo"};
const PROGMEM String MENU_CONF[] = {"1.-Tiempo", "2.-Mecanismo bloqueo", "3.-Otras opciones", "4.-Test"};
const PROGMEM String MENU_TIME[] = {"1.-Tiempo de juego", "2.-Tiempo bomba", "3.-Tiempo des/armado", "4.-Tiempo inicio"};
const PROGMEM String MENU_TIME2[] = {"Tiempo actual", "", "1.-Cambiar", "0.-Volver"};
const PROGMEM String MENU_LOCKERS[] = {"1.-Bloqueos activos", String("2.-Contrase") + (char)0xEE + String("a"), "3.-Cables", "4.-Llaves NFC"};
const PROGMEM String MENU_ACTIVE_LOCKERS[] = {String("1.-Contrase") + (char)0xEE + String("a"), "2.-Cables", "3.-Llaves NFC", ""};
const PROGMEM String MENU_PASS[] = {String("Contrase") + (char)0xEE + String("a actual"), "", "1.-Cambiar", "0.-Volver"};
const PROGMEM String NEW_PASS[] = {"Introduce la nueva", String("contrase") + (char)0xEE + String("a:"), "*Borrar #Confirmar", ""};
const PROGMEM String MENU_WIRE[] = {"Funcion cable", "1.-C1 =    2.-C2 =  ", "3.-C3 =    4.-C4 =", ""};
const PROGMEM String FUNCTION_WIRE[] = {"1.-Reducir tiempo", "2.-Parar bomba", "3.-No hacer nada", "4.-Explotar"};
const PROGMEM String MENU_NFC[] = {"1.-Opciones tarjeta", "2.-Leer tarjeta", "3.-Gravar tarjeta", ""};
const PROGMEM String MENU_NFC_CONF[] = {"1.-Tipo", "2.-Usos", "3.-Tiempo", ""};
const PROGMEM String MENU_NFC_TIPO[] = {"1.-Parar Bomba", String("2.-A") + (char)0xEE + String("adir tiempo"), "3.-Restar tiempo", ""};
const PROGMEM String MENU_NFC_USOS[] = {"Numero de usos", "de 1 a 9, o A para", "infinitos usos", ""};
const PROGMEM String MENU_OTHER_OPT[] = {"1.-Sonido", "2.-Alarma", "3.-Granada", "4.-Sensor golpes"};
const PROGMEM String MENU_SHOCK[] = {"1.-Sensor golpes", "2.-Ajuste sensivilidad", "Sensivilidad actual:", ""};
const PROGMEM String MENU_SHOCK2[] = {"1.-Ajuste manual", "2.-Ajuste por golpe", "Sensivilidad actual:", ""};
const PROGMEM String WAIT_FOR_SHOCK = {"Golpea el dispositivo"};
const PROGMEM String NFC_CARD_ON_READER = "Ponga la tarjeta NFC sobre el lector...";
const PROGMEM String WIN_MESSAGE_RED = "    RED TEAM WIN    ";
const PROGMEM String WIN_MESSAGE_GREEN = "   GREEN TEAM WIN   ";
const PROGMEM String DRAW = "DRAW";
const PROGMEM String PRESS_RED_BUTTON = "Pulsa el boton rojo";
const PROGMEM String PRESS_GREEN_BUTTON = "Pulsa el boton verde";
const PROGMEM String BOMB_ACTIVE = "BOMBA ARMADA";
const PROGMEM String BOMB_UNACTIVE = "BOMBA DESARMADA";
const PROGMEM String INTRO_TIME = "Introduce el tiempo:";
const PROGMEM String GAME_PASS = "PASS";
const PROGMEM String GAME_WIRE = "WIRE";
const PROGMEM String GAME_NFC = "NFC";
const PROGMEM String GAME_START_IN = "The game starts in";
const PROGMEM String RED_TEAM = "Red team";
const PROGMEM String GREEN_TEAM = "Green team";
const PROGMEM String INTRO2NUM[] = {"Introduce un valor", "de 2 digitos:", "", ""};
//------------------------------------------------------------------------------------

//-----------------------VARIABLES GLOVALES BOMBA--------------------------------------
bool bBUZZ = true;
bool bALARM = true;
bool bGRENADE = true;

bool bSHOCK = false;
byte SHOCK_SENSIBILITY = 75; 

bool bPASS = true; //bloqueo contraseña
String PASS = "123ABC"; //contraseña

bool bWIRE = false; //bloqueo cables
int tWIRE[4] = {2, 3, 3, 3};// efecto cable 1=-10seg 2=pararBomba 3=nada 4= booom!

bool bNFC = false; //bloqueo NFC

long RELOJ_JUEGO = 60000;//10 min en centisegundos
long RELOJ_BOMBA = 30000;//5 min en centisegundos
int TIME_ARMDES = 10; //tiempo armado/desarmado bomba en segundos
int INIT_TIME = 10; //tiempo para iniciar juego en segundos

//------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  Wire.begin();
  accel.begin();
  lcd.init();
  lcd.backlight();
  ld.setDigitLimit(8);//8 digitos
  SPI.begin();
  mfrc522.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    nfcKey.keyByte[i] = 0xFF;
  }
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
  showTime(RELOJ_BOMBA);
}

void loop() {
  setup2();
  menu();
}


