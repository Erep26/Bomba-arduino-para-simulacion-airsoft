//Menus

void menu() {
  printScreen(MENU_PRINCIPAL);
  drawBomb(17, 0);
  switch (validOption(1, 2)) {
    case 1:
      menuJuego();
      break;
    case 2:
      menuConfig();
      break;
  }
}

void menuJuego() {
  int opt;
  do {
    printScreen(MENU_JUEGO);
    drawBomb(17, 0);
    opt = validOption(0, 4);
    switch (opt) {
      case 1: //1.-Counterstrike
        waitFor(INIT_TIME);
        counterstrike();
        keypad.waitForKey();
        break;
      case 2: //2.-Asalto
        waitFor(INIT_TIME);
        assault();
        keypad.waitForKey();
        break;
      case 3: //3.-Dominacion
        waitFor(INIT_TIME);
        domination();
        keypad.waitForKey();
        break;
      case 4: //4.-Explosivo
        waitFor(INIT_TIME);
        explosive();
        keypad.waitForKey();
        break;
    }
  } while (opt != 0);
}

void menuConfig() {
  //1.-Tiempo", "2.-Mecanismo bloqueo", "3.-Otras opciones", "4.-Test
  int opt;
  do {
    printScreen(MENU_CONF);
    opt = validOption(0, 4);
    switch (opt) {
      case 1:
        menuTime();
        break;
      case 2:
        menuLockers();
        break;
      case 3:
        menuOtherOpt();
        break;
      case 4:
        test();
        break;
    }
  } while (opt != 0);
}

void menuTime() {
  //1.-Tiempo de juego", "2.-Tiempo bomba", "3.-Tiempo des/armado", "4.-Tiempo inicio
  int opt;
  do {
    printScreen(MENU_TIME);
    opt = validOption(0, 4);
    switch (opt) {
      case 1:
        while (opt != 0) {
          printScreen(MENU_TIME2);
          printLong(RELOJ_JUEGO, 0, 1);
          opt = validOption(0, 1);
          if (opt == 1) {
            int auxR[4];
            RELOJ_JUEGO = readTime(auxR);
          }
        }
        opt = -1;
        break;
      case 2:
        while (opt != 0) {
          printScreen(MENU_TIME2);
          printLong(RELOJ_BOMBA, 0, 1);
          opt = validOption(0, 1);
          if (opt == 1) {
            int auxR[4];
            RELOJ_BOMBA = readTime(auxR);
          }
        }
        opt = -1;
        break;
      case 3:
        while (opt != 0) {
          printScreen(MENU_TIME2);
          lcd.setCursor(0, 1);
          lcd.print(TIME_ARMDES);
          lcd.print(" segundos");
          opt = validOption(0, 1);
          if (opt == 1) TIME_ARMDES = readSeconds();
        }
        opt = -1;
        break;
      case 4:
        while (opt != 0) {
          printScreen(MENU_TIME2);
          lcd.setCursor(0, 1);
          lcd.print(INIT_TIME);
          lcd.print(" segundos");
          opt = validOption(0, 1);
          if (opt == 1) INIT_TIME = readSeconds();
        }
        opt = -1;
        break;
    }
  } while (opt != 0);
}

void menuLockers() {//1.-Bloqueos activos", "2.-Contraseña", "3.-Cables", "4.-Llaves NFC
  int opt;
  do {
    printScreen(MENU_LOCKERS);
    opt = validOption(0, 4);
    switch (opt) {
      case 1:
        menuActiveLockers();
        break;
      case 2:
        while (opt != 0) {
          printScreen(MENU_PASS);
          lcd.setCursor(0, 1);
          lcd.print(PASS);
          opt = validOption(0, 1);
          if (opt == 1) newPass();
        }
        opt = -1;
        break;
      case 3:
        while (opt != 0) {
          printScreen(MENU_WIRE);
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
            printScreen(FUNCTION_WIRE);
            tWIRE[opt - 1] = validOption(1, 4);
          }
        }
        opt = -1;
        break;
      case 4:
        menuNfc();
        break;
    }
  } while (opt != 0);
}

void menuNfc() {
  int opt;
  byte data[16] = {1, 1, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  //data[0] tipo
  //data[1] numero usos
  //data[2]:data[3]:data[4]:data[5] tiempo hh:mm:ss:ds
  do {
    printScreen(MENU_NFC);
    printData(data);
    opt = validOption(0, 3);
    switch (opt) {
      case 1:
        while (opt != 0) {//1.-Tipo", "2.-Usos", "3.-Tiempo", ""
          printScreen(MENU_NFC_CONF);
          printData(data);
          opt = validOption(0, 3);
          switch (opt) {
            case 1:
              printScreen(MENU_NFC_TIPO);
              data[0] = validOption(1, 3);
              break;
            case 2:
              printScreen(MENU_NFC_USOS);
              data[1] = validOption(1, 'A');// A = infinitos usos
              break;
            case 3:
              int auxR[4];
              readTime(auxR);
              for(int i = 0; i < 4; i++)
                data[i+2] = auxR[i];
              break;
          }
        }
        opt = -1;
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(NFC_CARD_ON_READER);
        while ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial());
        pita();
        byte readData[18];
        readBlock(2, readData);
        for (int i = 0; i < 16; i++)
          data[i] = readData[i];
        mfr_halt();
        break;
      case 3:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(NFC_CARD_ON_READER);
        while ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial());
        pita();
        writeBlock(2, data);
        mfr_halt();
        break;
    }
  } while (opt != 0);
  opt = -1;
}

void menuActiveLockers() {
  int opt;
  printScreen(MENU_ACTIVE_LOCKERS);
  do {
    check(MENU_ACTIVE_LOCKERS[0].length() + 1, 0, bPASS);
    check(MENU_ACTIVE_LOCKERS[1].length() + 1, 1, bWIRE);
    check(MENU_ACTIVE_LOCKERS[2].length() + 1, 2, bNFC);
    opt = validOption(0, 3);
    if (opt == 1) bPASS = !bPASS;//Contraseña
    if (opt == 2) bWIRE = !bWIRE;//Cables
    if (opt == 3) bNFC = !bNFC;//Llave NFC
  } while (opt != 0); //0.-Volver
}

void menuOtherOpt() {
  int opt;
  printScreen(MENU_OTHER_OPT);
  do {
    check(MENU_OTHER_OPT[0].length() + 1, 0, bBUZZ);
    check(MENU_OTHER_OPT[1].length() + 1, 1, bALARM);
    check(MENU_OTHER_OPT[2].length() + 1, 2, bGRENADE);
    opt = validOption(0, 3);
    if (opt == 1) bBUZZ = !bBUZZ;
    if (opt == 2) bALARM = !bALARM;
    if (opt == 3) bGRENADE = !bGRENADE;
    if (opt == 4) {

    }
  } while (opt != 0);
}

void test() {
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
    check(3, 0, boolRead(WIRE[0]));
    check(8, 0, boolRead(WIRE[1]));
    check(13, 0, boolRead(WIRE[2]));
    check(18, 0, boolRead(WIRE[3]));
    check(3, 1, boolRead(RED_BTN));
    check(8, 1, boolRead(GREEN_BTN));
    if (key == '#' && n > 1) n--;
    else if (key == '*' && n <= 7) n++;
    else if (key >= '0' && key <= '9') {
      byte nums[] = {B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011};
      ld.write(n, nums[key - '0']);
    }
    if (accel.available()) {
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
      mfr_halt();
    }
  } while (key != 'D');
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
  if (data[1] != 'A') lcd.print(data[1]);
  else lcd.print("A");
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
    if (opt > 9) opt += '0'; // si es una letra
  } while (opt < minOpt || opt > maxOpt);
  pita();
  return opt;
}

void printScreen(const String m[]) {
  lcd.clear();
  for (int i = 0; i < 4; i++) {
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

int readSeconds() {
  int s;
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(INTRO_TIME);
  lcd.setCursor(0, 2);
  s = validOption(0, 9) * 10;
  s += validOption(0, 9);
  return s;
}

long readTime(int t[4]) {
  const byte POINT = B10000000;
  const byte NUM[] = {B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011};
  //long h, m, s, cs;
  for (int i = 0; i < 4; i++)
    t[i] = 0;
  ld.clear();
  lcd.setCursor(0, 1);
  lcd.print(INTRO_TIME);
  lcd.setCursor(0, 2);
  lcd.print("  :  :  :  ");
  lcd.setCursor(0, 2);
  int key;
  for (int i = 0; i < 8; i++) {
    if (i == 2 || i == 4) key = validOption(0, 5);
    else key = validOption(0, 5);
    ld.write(8 - i, NUM[key] );
    lcd.print(key);
    t[(int)i / 2] += key;
    if (i % 2 == 0) t[(int)i / 2] *= 10;
    else lcd.print(":");
  }
  long mul_h = 360000,
       mul_m = 6000,
       mul_s = 100;
  long l = (t[0] * mul_h) + (t[1] * mul_m) + (t[2] * mul_s) + t[3];
  return l;
}

void printLong(long t, int col, int fil) {
  unsigned int h = t / 360000;
  unsigned int m = (t % 360000) / 6000;
  unsigned int s = ((t % 360000) % 6000) / 100;
  unsigned int cs = t % 100;
  lcd.setCursor(col, fil);
  if (h < 10) lcd.print("0");
  lcd.print(h);
  lcd.print(":");
  if (m < 10) lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if (s < 10) lcd.print("0");
  lcd.print(s);
  lcd.print(":");
  if (cs < 10) lcd.print("0");
  lcd.print(cs);
}

void newPass() {
  printScreen(NEW_PASS);
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
