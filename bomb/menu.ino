int menu() {
  String MENU[] = {"Menu", "1.-Iniciar juego", "2.-Configuracion"};
  String MENU1[] = {"Modos de juego", "1.-Bomba", "2.-Dominacion"};
  String MENU2[] = {"1.-Tiempo", "2.-Mecanismo bloqueo", "3.-Otras opciones", "4.-Test"};

  String MENU22[] = {"1.-Bloqueos activos", String("2.-Contrase") + (char)0xEE + String("a"), "3.-Cables", "4.-Llaves NFC"};
  String MENU221[] = {String("1.-Contrase") + (char)0xEE + String("a"), "2.-Cables", "3.-Llaves NFC"};
  String MENU222[] = {String("Contrase") + (char)0xEE + String("a actual"), "", "1.-Cambiar", "0.-Volver"};
  String MENU2221[] = {"Introduce la nueva", String("contrase") + (char)0xEE + String("a:"), "*Borrar #Confirmar"};
  String MENU223[] = {"Funcion cable", "1.-C1 =    2.-C2 =  ", "3.-C3 =    4.-C4 ="};
  String MENU223T[] = {"1.-Reducir tiempo", "2.-Parar bomba", "3.-No hacer nada", "4.-Explotar"};

  String MENU23[] = {"1.-Sonido", "2.-Alarma", "3.-Granada"};

  String MENU224[] = {"1.-Opciones tarjeta", "2.-Leer tarjeta", "3.-Gravar tarjeta"};
  String MENU2241[] = {"1.-Tipo", "2.-Usos", "3.-Tiempo"};
  String MENU22411[] = {"1.-Parar Bomba", String("2.-A") + (char)0xEE + String("adir tiempo"), "3.-Restar tiempo"};
  String MENU22412[] = {"Numero de usos", "de 1 a 9"};

  printMenu(MENU, 3);
  drawBomb(17, 0);
  int opt = validOption(1, 2);
  if (opt == 1) { //1.-Iniciar juego
    while (opt != 0) { //0.-Volver
      printMenu(MENU1, 3);
      drawBomb(17, 0);
      opt = validOption(0, 2);
      switch (opt) {
        case 1: //1.-Bomba
          game();
          return 0;
          break;
        case 2: //2.-Dominacion
          dommination();
          return 0;
          break;
      }
    }
    opt = -1;
  }
  else if (opt == 2) { // 2.-Configuracion


    while (opt != 0) { //0.-Volver
      printMenu(MENU2, 4);
      //drawBomb(17, 0);
      opt = validOption(0, 4);
      if (opt == 1) { //1.-Tiempo
        ld.clear();
        readTime();
      }
      else if (opt == 2) { //2.-Mecanismos bloqueo

        while (opt != 0) { //0.-Volver
          printMenu(MENU22, 4);
          opt = validOption(0, 4);
          if (opt == 1) {//Bloqueos activos
            while (opt != 0) { //0.-Volver
              printMenu(MENU221, 3);
              check(MENU221[0].length() + 1, 0, bPASS);
              check(MENU221[1].length() + 1, 1, bWIRE);
              check(MENU221[2].length() + 1, 2, bKEYS);
              opt = validOption(0, 3);
              if (opt == 1) bPASS = !bPASS;//Contraseña
              if (opt == 2) bWIRE = !bWIRE;//Cables
              if (opt == 3) bKEYS = !bKEYS;//Llave NFC
            }
            opt = -1;
          }
          else if (opt == 2) { //contraseña
            while (opt != 0) { //0.-Volver
              MENU222[1] = PASS;
              printMenu(MENU222, 4);
              opt = validOption(0, 1);
              if (opt == 1) {
                printMenu(MENU2221, 3);
                newPass();
              }
            }
            opt = -1;
          }
          else if (opt == 3) { //Cables
            while (opt != 0) { //0.-Volver
              printMenu(MENU223, 3);
              lcd.setCursor(8, 1);
              lcd.print(tWIRE[0]);
              lcd.setCursor(19, 1);
              lcd.print(tWIRE[1]);
              lcd.setCursor(8, 2);
              lcd.print(tWIRE[2]);
              lcd.setCursor(19, 2);
              lcd.print(tWIRE[3]);

              opt = validOption(0, 4);
              if (opt != 0) {
                printMenu(MENU223T, 4);
                int opt2 = validOption(1, 4);
                tWIRE[opt - 1] = opt2;
              }
            }
            opt = -1;
          }
          else if (opt == 4) {
            byte data[16] = {1, 1, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            //data[0] tipo
            //data[1] numero usos
            //data[2]:data[3]:data[4]:data[5] tiempo hh:mm:ss:ds
            while (opt != 0) { //0.-Volver
              printMenu(MENU224, 3);
              printData(data);
              opt = validOption(0, 3);
              if (opt == 1) { //1.-Opciones tarjeta
                while (opt != 0) { //0.-Volver
                  printMenu(MENU2241, 3);
                  printData(data);
                  opt = validOption(0, 3);
                  if (opt == 1) { //1.-Tipo
                    printMenu(MENU22411, 3);
                    data[0] = validOption(1, 3);
                    //1.-Parar Bomba
                    //2.-Añadir tiempo
                    //3.-Restar tiempo
                  }
                  if (opt == 2) { //2.-Usos
                    printMenu(MENU22412, 2);
                    data[1] = validOption(1, 9);
                  }
                  if (opt == 3) { //3.-Tiempo
                    byte nfcClock[4];
                    nfcReadTime(nfcClock);
                    for (int i = 0; i < 4; i++)
                      data[i + 2] = nfcClock[i];
                  }
                }
                opt = -1;
              }
              if (opt == 2) { //2.-Leer tarjeta
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Ponga la tarjeta NFC sobre el lector...");
                while ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial());
                pita();
                byte readData[18];
                readBlock(2, readData);
                for (int i = 0; i < 16; i++)
                  data[i] = readData[i];
                mfr_halt();
              }
              if (opt == 3) { //3.-Gravar tarjeta
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Ponga la tarjeta NFC sobre el lector...");
                while ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial());
                pita();
                writeBlock(2, data);
                mfr_halt();
              }
            }
            opt = -1;
          }

        }
        opt = -1;

      }
      else if (opt == 3) { //3.Otras opciones
        while (opt != 0) {
          printMenu(MENU23, 3);
          check(MENU23[0].length() + 1, 0, bBUZZ);
          check(MENU23[1].length() + 1, 1, bALARM);
          check(MENU23[2].length() + 1, 2, bGRENADE);
          opt = validOption(0, 3);
          if (opt == 1) bBUZZ = !bBUZZ;
          if (opt == 2) bALARM = !bALARM;
          if (opt == 3) bGRENADE = !bGRENADE;
        }
        opt = -1;
      }
      else if (opt == 4) {//4.-Test
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("C1 o C2 o C3 o C4 o");
        lcd.setCursor(0, 1);
        lcd.print("B1 o B2 o");
        lcd.setCursor(0, 3);
        lcd.print("NFC");
        char key;
        int n = 8;
        do {
          key = keypad.getKey();
          inputTest();
          if (key == '#' && n > 1) n--;
          else if (key == '*' && n <= 7) n++;
          else if (key >= '0' && key <= '9') {
            byte nums[] = {B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011};
            ld.write(n, nums[key - '0']);
          }
          if (accel.available()) {
            //lcdBorra(0, 2, 19, 2);
            lcd.setCursor(0, 2);
            lcd.print(accel.getCalculatedX(), 2);
            lcd.print("X");
            lcd.print(accel.getCalculatedY(), 2);
            lcd.print("Y");
            lcd.print(accel.getCalculatedZ(), 2);
            lcd.print("Z");
          }
          if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
            lcdBorra(4, 3, 19, 3);
            lcd.setCursor(4, 3);
            
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                lcd.print(mfrc522.uid.uidByte[i], HEX);
             }

            /*
            byte readData[18];
            readBlock(2, readData);
            lcdBorra(0, 3, 19, 3);
            lcd.setCursor(0, 3);
            for (int i = 0; i < 10; i++)
              lcd.print(readData[i]);*/
            mfr_halt();
          }
        } while (key != 'D');
      }
    }
  }
}

void inputTest() {
  check(3, 0, boolRead(WIRE[0]));
  check(8, 0, boolRead(WIRE[1]));
  check(13, 0, boolRead(WIRE[2]));
  check(18, 0, boolRead(WIRE[3]));
  check(3, 1, boolRead(RED_BTN));
  check(8, 1, boolRead(GREEN_BTN));
}

void drawBomb(int col, int fil) {
  byte bo0[] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x04, 0x0C};
  byte bo1[] = {0x00, 0x00, 0x11, 0x0A, 0x13, 0x08, 0x16, 0x05};
  byte bo2[] = {0x01, 0x03, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x1F};
  byte bo3[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  byte bo4[] = {0x00, 0x18, 0x1C, 0x1C, 0x1E, 0x1E, 0x1E, 0x1E};
  byte bo5[] = {0x1F, 0x0F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00};
  byte bo6[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00};
  byte bo7[] = {0x1E, 0x1C, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x00};

  lcd.createChar(0, bo0);
  lcd.createChar(1, bo1);
  lcd.createChar(2, bo2);
  lcd.createChar(3, bo3);
  lcd.createChar(4, bo4);
  lcd.createChar(5, bo5);
  lcd.createChar(6, bo6);
  lcd.createChar(7, bo7);

  lcd.setCursor(col, fil);
  lcd.print(" ");
  lcd.write(0);
  lcd.write(1);
  lcd.setCursor(col, fil + 1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, fil + 2);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);
}

void printData(byte data[]) {
  lcd.setCursor(0, 3);
  lcd.print(data[0]);
  lcd.print(+ " ; ");
  lcd.print(data[1]);
  lcd.print(" ; ");
  if (data[2] < 10) lcd.print("0");
  lcd.print(data[2]);
  lcd.print(":");
  if (data[3] < 10) lcd.print("0");
  lcd.print(data[3]);
  lcd.print(":");
  if (data[4] < 10) lcd.print("0");
  lcd.print(data[4]);
  lcd.print(":");
  if (data[5] < 10) lcd.print("0");
  lcd.print(data[5]);
}


int validOption(int minOpt, int maxOpt) {
  int opt;
  do {
    opt = keypad.waitForKey() - '0';
  } while (opt < minOpt || opt > maxOpt);
  pita();
  return opt;
}

void printMenu(String m[], int n) {
  lcd.clear();
  for (int i = 0; i < n; i++) {
    lcd.setCursor(0, i);
    lcd.print(m[i]);
  }
}

void lcdBorra(int col, int fil, int endCol, int endFil) {
  for (int f = fil; f <= endFil; f++)
    for (int c = col; c <= endCol; c++) {
      lcd.setCursor(c, f);
      lcd.print(" ");
    }
}

void nfcReadTime(byte t[4]) {
  lcd.setCursor(8, 3);
  lcd.print("  :  :  :  ");
  lcd.setCursor(8, 3);
  for (int i = 8; i > 0; i--) {
    char key = 10;
    while (key < '0' || key > '9' || ((i == 6 || i == 4) && key > '5'))
      key = keypad.getKey();
    pita();
    lcd.print(key);
    switch (i) {
      case 8:
        t[0] = (key - '0') * 10;
        break;
      case 7:
        t[0] += key - '0';
        lcd.print(":");
        break;
      case 6:
        t[1] = (key - '0') * 10;
        break;
      case 5:
        t[1] += key - '0';
        lcd.print(":");
        break;
      case 4:
        t[2] = (key - '0') * 10;
        break;
      case 3:
        t[2] += key - '0';
        lcd.print(":");
        break;
      case 2:
        t[3] = (key - '0') * 10;
        break;
      case 1:
        t[3] += key - '0';
        break;
    }
  }
}

void readTime() {
  //const byte NUM[] = {B11111110,B10110000,B11101101,B11111001,B10110011,B11011011,B11011111,B11110000,B11111111,B11111011};
  const byte POINT = B10000000;
  const byte NUM[] = {B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011};
  long h, m, s, cs;
  lcdBorra(0, 1, 16, 3);
  lcd.setCursor(0, 1);
  lcd.print("Introduce el tiempo:");
  lcd.setCursor(0, 2);
  lcd.print("  :  :  :  ");
  lcd.setCursor(0, 2);
  for (int i = 8; i > 0; i--) {
    char key = 10;
    while (key < '0' || key > '9' || ((i == 6 || i == 4) && key > '5'))
      key = keypad.getKey();
    pita();
    ld.write(i, NUM[key - '0'] );
    lcd.print(key);
    switch (i) {
      case 8:
        h = (key - '0') * 10;
        break;
      case 7:
        h += key - '0';
        lcd.print(":");
        break;
      case 6:
        m = (key - '0') * 10;
        Serial.println(m);
        break;
      case 5:
        m += key - '0';
        Serial.println(m);
        lcd.print(":");
        break;
      case 4:
        s = (key - '0') * 10;
        Serial.println(s);
        break;
      case 3:
        s += key - '0';
        Serial.println(s);
        lcd.print(":");
        break;
      case 2:
        cs = (key - '0') * 10;
        Serial.println(cs);
        break;
      case 1:
        cs += key - '0';
        Serial.println(cs);
        break;
    }
  }
  RELOJ = h * 360000 + m * 6000 + s * 100 + cs;
  Serial.println(RELOJ);
}

void newPass() {
  lcdBorra(0, 3, 19, 3);
  char auxPass[20];
  char key;
  int i = 0;
  do {
    key = keypad.waitForKey();
    pita();
    if (key == '*' && i != 0) i--;
    else if (key != '#' && key != '*' && i < 20) {
      auxPass[i] = key;
      i++;
    }
    lcdBorra(0, 3, 19, 3);
    for (int i2 = 0; i2 < i; i2++) {
      lcd.setCursor(i2, 3);
      lcd.print(auxPass[i2]);
    }
  } while (key != '#');
  if (i == 0) PASS = "";
  else PASS = String(auxPass).substring(0, i);
}

void check(int col, int fil , bool yesno) {
  byte noCheck[] = {0x00, 0x1F, 0x11, 0x11, 0x11, 0x1F, 0x00, 0x00};
  byte yesCheck[] = {0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00};
  lcd.createChar(0, noCheck);
  lcd.createChar(1, yesCheck);
  lcd.setCursor(col, fil);
  lcd.write((int)yesno);
}
