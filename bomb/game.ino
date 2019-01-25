unsigned long TIME_PUNTUA = millis();
void puntua(unsigned long nteam) {
  unsigned long time = millis();
  if (time - TIME_PUNTUA >= 10) {
    TIME_PUNTUA = time;
    nteam += 10;
  }
}

void dommination() {
  unsigned long reloj = RELOJ,
                team1 = 0,
                team2 = 0;
  while (!ENDGAME) {
    counter(reloj);
    buzzing();
    percentageBomb(reloj);
    if (DOMAIN[0]) puntua(team1);
    if (DOMAIN[1]) puntua(team2);
    if (reloj == 0) ENDGAME = true;
  }
  if (team1 > team2) { //gana equipo 1

  }
  else if (team1 < team2) { //gana equipo 2

  }
  else; //empate
  alarm();
}

void printGames(bool bp, bool bw, bool bk) {
  lcdBorra(0, 0, 19, 0);
  lcd.setCursor(0, 0);
  if (bp) lcd.print("Pass?");
  if (bw) lcd.print("Wires?");
  if (bk) lcd.print("Keys?");
}

bool checkWire(int n, unsigned long &reloj) {
  switch (n) {
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

int game() {
  unsigned long reloj = RELOJ;
  String pass = "";
  bool bp = bPASS,
       bw = bWIRE,
       bk = bKEYS;
  drawEmptyProgressBar();
  printGames(bp, bw, bk);
  while (!ENDGAME) {
    counter(reloj);
    buzzing();
    percentageBomb(reloj);

    if (reloj <= 0) {
      ENDGAME = true;
      reloj = 0;
    }

    if (bp && readChar(pass) && PASS == pass) {
      bp = false;
      if (!bw && !bk) {
        ENDGAME = true;
        WIN = true;
      }
      else printGames(bp, bw, bk);
    }

    if (bw) {
      if (digitalRead(WIRE1) && !CUTTED_WIRE[0]) {
        CUTTED_WIRE[0] = true;
        if (checkWire(tWIRE[0], reloj)) bw = false;
        else printGames(bp, bw, bk);
      }
      if (digitalRead(WIRE2) && !CUTTED_WIRE[1]) {
        CUTTED_WIRE[1] = true;
        if (checkWire(tWIRE[1], reloj)) bw = false;
        else printGames(bp, bw, bk);
      }
      if (digitalRead(WIRE3) && !CUTTED_WIRE[2]) {
        CUTTED_WIRE[2] = true;
        if (checkWire(tWIRE[2], reloj)) bw = false;
        else printGames(bp, bw, bk);
      }
      if (digitalRead(WIRE4) && !CUTTED_WIRE[3]) {
        CUTTED_WIRE[3] = true;
        if (checkWire(tWIRE[3], reloj)) bw = false;
        else printGames(bp, bw, bk);
      }
    }

    if (bk) {

    }

    if (!bp && !bw && !bk) {
      ENDGAME = true;
      WIN = true;
    }

  }
  /*
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pulsa * durante 5s");
    lcd.setCursor(0, 2);
    lcd.print("para resetear");
    lcd.setCursor(0, 3);
    lcd.print("el dispositivo");*/

  if (WIN) {
    lcd.setCursor(3, 2);
    lcd.print("Bomba desactivada");
  }
  else {
    lcd.setCursor(5, 2);
    lcd.print("Bomba explotada");
    alarm();
  }

  lcd.setCursor(0, 0);
  lcd.print("Pulsa * para volver");
  lcd.setCursor(0, 1);
  lcd.print("al menu principal");
  while (keypad.waitForKey() != '*');
}

unsigned long TIME_COUNTER = millis();
void counter(unsigned long &reloj) {
  unsigned long time = millis();
  if (time - TIME_COUNTER >= 10) {
    TIME_COUNTER = time;
    reloj -= 10;
    showTime(reloj);
  }
}

void percentageBomb(unsigned long reloj) {
  byte bar10[] = {0x0F, 0x18, 0x13, 0x17, 0x17, 0x13, 0x18, 0x0F}; //punta izquierda llena
  byte bar11[] = {0x1F, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x1F}; //centro mitad
  byte bar12[] = {0x1F, 0x00, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x1F}; //centro lleno
  byte bar13[] = {0x1E, 0x03, 0x19, 0x1D, 0x1D, 0x19, 0x03, 0x1E}; //punta derecha llena

  lcd.createChar(3, bar10);
  lcd.createChar(4, bar11);
  lcd.createChar(5, bar12);
  lcd.createChar(6, bar13);

  int x = (((reloj * 100) / RELOJ) * -1) + 100;
  lcd.setCursor(0, 2);
  lcd.print(x);
  lcd.print("%");
  x = int((float(x) / 100) * 20);
  for (int i = 1; i < x; i++)
  {
    lcd.setCursor(i - 1, 3);
    if (i == 1) lcd.write(3);
    if (i > 1) lcd.write(5);
  }
  if (reloj == 0) {
    lcd.setCursor(19, 3);
    lcd.write(6);
  }
}

void drawEmptyProgressBar() {
  //barra vacia
  byte bar00[] = {0x0F, 0x18, 0x10, 0x10, 0x10, 0x10, 0x18, 0x0F}; //punta izquierda
  byte bar01[] = {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}; //centro
  byte bar02[] = {0x1E, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x1E}; //punta derecha

  lcd.createChar(0, bar00);
  lcd.createChar(1, bar01);
  lcd.createChar(2, bar02);

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.write(0);
  lcd.setCursor(19, 3);
  lcd.write(2);
  for (int i = 1; i < 19; i++) {
    lcd.setCursor(i, 3);
    lcd.write(1);
  }
}

void showTime(unsigned long t) {
  //const byte NUM[] = {B11111110,B10110000,B11101101,B11111001,B10110011,B11011011,B11011111,B11110000,B11111111,B11111011};
  const byte POINT = B10000000;
  const byte NUM[] = {B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011};
  int h = t / 360000;
  int m = ((t / 100) % 3600) / 60;
  int s = ((t / 100) % 3600) % 60;
  int cs = t % 100;
  /*  lcd.clear();
    lcd.print(h);
    lcd.print(":");
    lcd.print(m);
    lcd.print(":");
    lcd.print(s);
    lcd.print(":");
    lcd.print(cs);*/

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


bool readChar(String &p) {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '#':
        return true;
        break;
      case '*':
        p = "";
        lcdBorra(0, 1, 19, 1);
        break;
      default:
        p += key;
        lcdBorra(0, 1, 19, 1);
        lcd.setCursor(0, 1);
        for (int i = 0; i < p.length(); i++) lcd.print('*');
        break;
    }
  }
  return false;
}

unsigned long TIME_BUZZING = millis();
void buzzing() {
  if (bBUZZ) {
    unsigned long time = millis();
    if (time - TIME_BUZZING >= 1000) {
      TIME_BUZZING = time;
      tone(BUZZPIN, 220, 100);
    }
  }
}

void alarm() {
  if (bALARM) digitalWrite(ALARMPIN, HIGH);
}

void grenade() {
  if (bGRENADE) digitalWrite(GRENADEPIN, HIGH);
  delay(1000);
  digitalWrite(GRENADEPIN, LOW);
}
