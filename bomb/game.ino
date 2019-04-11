//  Funciones usadas por los distitos modos de juego



bool boolRead(int n) {
  if (digitalRead(n) == HIGH) return true;
  else return false;
}

int calculatePercentage(long passedTime, long maxTime) {
  return (int)((passedTime * 100) / maxTime);
}

bool countMillis(int t, long &counted) {
  if ((millis() - counted) >= t) {
    counted = millis();
    return true;
  }
  return false;
}

bool checkPass(String &p) {
  char key = keypad.getKey();
  if (key) {
    pita();
    switch (key) {
      case '#':
        if (p == PASS) {
          p = "";
          return true;
        }
        break;
      case '*':
        p = "";
        lcdBorra(0, 1, 19, 1);
        break;
      default:
        if (p.length() < 20) {
          p += key;
          lcdBorra(0, 1, 19, 1);
          lcd.setCursor(0, 1);
          for (int i = 0; i < p.length(); i++) lcd.print('*');
        }
        break;
    }
  }
  return false;
}

bool checkWire(long &reloj, bool cuttedWire[]) {
  for (int i = 0; i < 4; i++) {
    if (boolRead(WIRE[i]) && !cuttedWire[i]) {
      cuttedWire[i] = true;
      pita();
      switch (tWIRE[i]) {
        case 1: //-10 seg
          reloj -= 1000;
          break;
        case 2: //Cable correcto
          return true;
          break;
        case 3:
          // No hago nada ;P
          break;
        case 4: //BOOM!!!
          reloj = 0;
          break;
      }
    }
  }
  return false;
}

bool checkNFC(long &reloj) {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    byte readData[18];
    readNFC(readData);
    mfr_halt();
    if (readData[1] > 0) {
      pita();
      if (readData[1] != 'A') readData[1]--;
      writeNFC(readData);
      if (readData[0] == 1) {
        return true;
      }
      else {
        long r = readData[2] * 360000 + readData[3] * 6000 + readData[4] * 100 + readData[5];
        if (readData[0] == 2) {
          reloj -= r;
          if (reloj > 35999999) reloj = 35999999;
        }
        else if (readData[0] == 3) {
          reloj += r;
          if (reloj < 0) reloj = 0;
        }
      }
    }
  }
  return false;
}

void waitFor(int s) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(GAME_START_IN);
  long t = millis();
  if (((int)s / 10) > 0) {
    customNum(((int)s / 10), 7, 1);
    customNum(((int)s % 10), 10, 1);
  }
  else customNum(((int)s % 10), 8, 1);
  while (s != 0) {
    if (millis() - t > 1000) {
      t = millis();
      s--;
      if (((int)s / 10) > 0) {
        customNum(((int)s / 10), 7, 1);
        customNum(((int)s % 10), 10, 1);
      }
      else {
        if (s % 10 == 9) {
          lcdBorra(7, 1, 8, 2);
          lcdBorra(11, 1, 13, 2);
        }
        customNum(((int)s % 10), 8, 1);
      }
    }
  }
  lcd.clear();
}

void showTime( long t) {
  //const byte NUM[] = {B11111110,B10110000,B11101101,B11111001,B10110011,B11011011,B11011111,B11110000,B11111111,B11111011};
  const byte POINT = B10000000;
  const byte NUM[] = {B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011};
  int h = t / 360000;
  int m = ((t / 100) % 3600) / 60;
  int s = ((t / 100) % 3600) % 60;
  int cs = t % 100;

  ld.write(8, NUM[(int)h / 10] );
  ld.write(7, NUM[(int)h % 10] + (POINT /** (cs / 10 % 2)*/));
  ld.write(6, NUM[(int)m / 10] );
  ld.write(5, NUM[(int)m % 10] + (POINT /** (cs / 10 % 2)*/));
  ld.write(4, NUM[(int)s / 10] );
  ld.write(3, NUM[(int)s % 10] + (POINT /** (cs / 10 % 2)*/));
  ld.write(2, NUM[(int)cs / 10] );
  ld.write(1, NUM[(int)cs % 10] );

  if (millis() / 500 % 2) ld.setBright(1);
  else ld.setBright(15);
}


void drawProgressBar(int percentage, int fila) {

  byte bar10[] = {0x0F, 0x18, 0x13, 0x17, 0x17, 0x13, 0x18, 0x0F}; //punta izquierda llena
  byte bar11[] = {0x1F, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x1F}; //centro mitad
  byte bar12[] = {0x1F, 0x00, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x1F}; //centro lleno
  byte bar13[] = {0x1E, 0x03, 0x19, 0x1D, 0x1D, 0x19, 0x03, 0x1E}; //punta derecha llena

  lcd.createChar(3, bar10);
  lcd.createChar(4, bar11);
  lcd.createChar(5, bar12);
  lcd.createChar(6, bar13);

  int x2 = (percentage * 30) / 100;

  for (int x = 0; x <= x2; x++) {
    if (x == 1) {
      lcd.setCursor(0, fila);
      lcd.write(3);
    }
    else if (((int)x / 2) != 0) {
      lcd.setCursor(((int)x / 2), fila);
      if (x % 2 == 1) lcd.write(5);
      else lcd.write(4);
    }
  }

  if (percentage == 100) {
    lcd.setCursor(15, fila);
    lcd.write(6);
  }

  lcd.setCursor(16, fila);
  if (percentage < 100) lcd.print(" ");
  if (percentage < 10) lcd.print(" ");
  lcd.print(percentage);
  lcd.print("%");
}

void drawEmptyProgressBar(int fila) {
  //barra vacia
  byte bar00[] = {0x0F, 0x18, 0x10, 0x10, 0x10, 0x10, 0x18, 0x0F}; //punta izquierda
  byte bar01[] = {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}; //centro
  byte bar02[] = {0x1E, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x1E}; //punta derecha

  lcd.createChar(0, bar00);
  lcd.createChar(1, bar01);
  lcd.createChar(2, bar02);

  lcd.setCursor(0, fila);
  lcd.write(0);
  for (int i = 1; i < 15; i++) {
    lcd.setCursor(i, fila);
    lcd.write(1);
  }
  lcd.setCursor(15, fila);
  lcd.write(2);
  lcd.print("  0%");
}

void printActiveGames(bool bp, bool bw, bool bk, int fila, bool verde) {
  lcdBorra(0, fila, 19, fila);
  lcd.setCursor(0, fila);
  if (bp) lcd.print(GAME_PASS);
  if (bw) {
    if (bp) lcd.print(";");
    lcd.print(GAME_WIRE);
  }
  if (bk) {
    if (bp || bw) lcd.print(";");
    lcd.print(GAME_NFC);
  }

  if (!bp && !bw && !bk) {
    if (verde) lcd.print(PRESS_GREEN_BUTTON);
    else lcd.print(PRESS_RED_BUTTON);
  }
}

void customNum(int num, int col, int fil) {
  byte LT[8] = {0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  byte UB[8] = {0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00};
  byte RT[8] = {0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  byte LL[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07};
  byte LB[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F};
  byte LR[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C};
  byte MB[8] = {0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F};
  byte block[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, MB);
  lcd.createChar(7, block);

  lcd.setCursor(col, fil);

  switch (num) {
    case 0:
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
      lcd.setCursor(col, fil + 1);
      lcd.write(3);
      lcd.write(4);
      lcd.write(5);
      break;
    case 1:
      lcd.write(1);
      lcd.write(2);
      lcd.print(" ");
      lcd.setCursor(col, fil + 1);
      lcd.write(4);
      lcd.write(7);
      lcd.write(4);
      break;
    case 2:
      lcd.write(6);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(col, fil + 1);
      lcd.write(3);
      lcd.write(4);
      lcd.write(4);
      break;
    case 3:
      lcd.write(6);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(col, fil + 1);
      lcd.write(4);
      lcd.write(4);
      lcd.write(5);
      break;
    case 4:
      lcd.write(3);
      lcd.write(4);
      lcd.write(7);
      lcd.setCursor(col, fil + 1);
      lcd.print(" ");
      lcd.print(" ");
      lcd.write(7);
      break;
    case 5:
      lcd.write(3);
      lcd.write(6);
      lcd.write(6);
      lcd.setCursor(col, fil + 1);
      lcd.write(4);
      lcd.write(4);
      lcd.write(5);
      break;
    case 6:
      lcd.write(0);
      lcd.write(6);
      lcd.write(6);
      lcd.setCursor(col, fil + 1);
      lcd.write(3);
      lcd.write(4);
      lcd.write(5);
      break;
    case 7:
      lcd.write(1);
      lcd.write(1);
      lcd.write(2);
      lcd.setCursor(col, fil + 1);
      lcd.print(" ");
      lcd.print(" ");
      lcd.write(7);
      break;
    case 8:
      lcd.write(0);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(col, fil + 1);
      lcd.write(3);
      lcd.write(4);
      lcd.write(5);
      break;
    case 9:
      lcd.write(0);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(col, fil + 1);
      lcd.print(" ");
      lcd.print(" ");
      lcd.write(7);
      break;
  }
}

long TIME_BUZZING = millis();
void buzzing() {
  if (bBUZZ) {
    long time = millis();
    if (time - TIME_BUZZING >= 1000) {
      TIME_BUZZING = time;
      tone(BUZZPIN, 220, 100);
    }
  }
}

void pita() {
  tone(BUZZPIN, 500, 100);
}

void alarm(bool b) {
  //if (bALARM && b) digitalWrite(ALARMPIN, HIGH);
}

void grenade() {
  if (bGRENADE) digitalWrite(GRENADEPIN, HIGH);
  delay(1000);
  digitalWrite(GRENADEPIN, LOW);
}

void winMessage(bool b, int fil) {
  lcd.setCursor(0, fil);
  if (b) lcd.print(WIN_MESSAGE_GREEN);
  else lcd.print(WIN_MESSAGE_RED);
}

int pushedButton_reloj = 0;
long pushedButton_counter = millis();
bool pushedButton(int button, bool hilow, int fila) {
  if (boolRead(button) == hilow) {
    if (TIME_ARMDES == 0) return true;
    if (pushedButton_reloj == 0) drawEmptyProgressBar(fila);
    if (countMillis(1000, pushedButton_counter)) pushedButton_reloj++;
    int x = calculatePercentage(pushedButton_reloj, TIME_ARMDES);
    drawProgressBar(x, fila);
    if (pushedButton_reloj == TIME_ARMDES) {
      pushedButton_reloj = 0;
      return true;
    }
  }
  else {
    pushedButton_counter = millis();
    pushedButton_reloj = 0;
    lcdBorra(0, fila, 19, fila);
  }
  return false;
}
