void drawBomb(int col, int fil){
  byte q[] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x04, 0x0C};
  byte w[] = {0x00, 0x00, 0x11, 0x0A, 0x13, 0x08, 0x16, 0x05};
  byte a[] = {0x01, 0x03, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x1F};
  byte s[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  byte d[] = {0x00, 0x18, 0x1C, 0x1C, 0x1E, 0x1E, 0x1E, 0x1E};
  byte z[] = {0x1F, 0x0F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00};
  byte x[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00};
  byte c[] = {0x1E, 0x1C, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x00};

  lcd.createChar(0, q);
  lcd.createChar(1, w);
  lcd.createChar(2, a);
  lcd.createChar(3, s);
  lcd.createChar(4, d);
  lcd.createChar(5, z);
  lcd.createChar(6, x);
  lcd.createChar(7, c);

  lcd.setCursor(col, fil);
  lcd.print(" ");
  lcd.write(0);
  lcd.write(1);
  lcd.setCursor(col, fil+1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, fil+2);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);
  }

void menu(){
  int opt;
  do{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Menu");
    lcd.setCursor(0,1);
    lcd.print("1.-Iniciar juego");
    lcd.setCursor(0,2);
    lcd.print("2.-Configuracion");
    drawBomb(17, 1);
  
    do{
      opt = keypad.waitForKey() - '0';
    }while(opt < 1 || opt > 2);
    if(opt == 2) menuConf();
  }while(opt != 1);
}

void lcdBorra(int col, int fil, int endCol, int endFil){
  for(int f = fil; f <= endFil; f++)
    for(int c = col; c <= endCol; c++){
      lcd.setCursor(c, f);
      lcd.print(" ");
    }
}

int menuConf(){
  
  int maxOpt = 5;
  char *confMen[maxOpt] ={ "1.Tiempo",
                        "2.Contrase0a",
                        "3.Etc",
                        "4.Etc",
                        "5.Volver"};
  confMen[1][10] = (char)0xEE;
  int opt;
  do{
    opt = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Configuracion");
    drawBomb(17, 1);

    unsigned long DELAY = millis();
    while(opt < 1 || opt > maxOpt){
      int j = 1;
      for(int i = 0; i < maxOpt && !(opt > 0 && opt <= maxOpt);){ //guarrada
        opt = keypad.getKey() - '0';
        if(millis()- DELAY >= 1000){
          i++;
          DELAY = millis();
          j = 1;
        }
        if(j){
          lcdBorra(0, 1, 16, 3);
          for(int i2 = i; i2 < i+3; i2++){
            lcd.setCursor(0, i2-i +1);
            if(i2 < maxOpt) lcd.print(confMen[i2]);
          }
          j=0;
        }
      }

      
    }

    
    switch(opt){
      case 1:
        lcdBorra(0, 1, 16, 3);
        lcd.setCursor(0, 1);
        lcd.print("Introduce el tiempo:");
        lcd.setCursor(0, 2);
        lcd.print("00:00:00:00");
        readTime();
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
    }
  }while(opt != maxOpt);
}

void readTime(){
  unsigned long h, m, s, cs;
  lcd.setCursor(0, 2);
  for(int i = 8; i > 0; i--){
    char key = 10;
    while(key < '0' || key > '9' || ((i == 6 || i == 4) && key > '5'))
      key = keypad.getKey();
    ld.write(i, NUM[key - '0'] );
    lcd.print(key);
    switch(i){
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
RELOJ = h * 360000 + m *6000 + s * 100 + cs;
Serial.println(RELOJ);
}
