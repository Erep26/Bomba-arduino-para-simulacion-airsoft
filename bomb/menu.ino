void drawBomb(int col, int fil){
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
  lcd.setCursor(col, fil+1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, fil+2);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);
}



int validOption(int minOpt, int maxOpt){
  int opt;
  do{
      opt = keypad.waitForKey() - '0';
  }while(opt < minOpt || opt > maxOpt);
  return opt;
}

void printMenu(String m[], int n){
  lcd.clear();
  for(int i = 0; i < n -1; i++){
    lcd.setCursor(0,i);
    lcd.print(m[i]);
  }
  lcd.setCursor(19-m[n-1].length(), 3);
}

void menu(){
  String MENU[] = {"Menu","1.-Iniciar juego","2.-Configuracion",""};
  String MENU1[] = {"Modos de juego","1.-Bomba","2.-Dominacion","3.-Volver"};
  String MENU2[] = {"1.-Tiempo", "2.-Seleccion juegos", "3.Bomba armada", "4.Otras opciones","5.-Volver"};
  String MENU22[] = {String("1.-Contrase") + (char)0xEE + String("a"), "2.-Cables", "3.-Llaves NFC", "4.-Volver"};
  
  printMenu(MENU,4);
  drawBomb(17, 0);
  int opt = validOption(1, 2);
  if(opt == 1){ //1.-Iniciar juego
    while(opt != 3){//3.-Volver
      printMenu(MENU1,4);
      drawBomb(17, 0);
      opt = validOption(1, 3);
      switch(opt){
        case 1: //1.-Bomba
          game();
          break;
        case 2: //2.-Dominacion
          dommination();
          break;
      }
    }
  }
  else if(opt == 2){ // 2.-Configuracion
    while(opt != 5){//5.-Volver
      printMenu(MENU2,5);
      drawBomb(17, 0);
      opt = validOption(1, 5);
      if(opt == 1){ //1.-Tiempo
        lcdBorra(0, 1, 16, 3);
        lcd.setCursor(0, 1);
        lcd.print("Introduce el tiempo:");
        lcd.setCursor(0, 2);
        lcd.print("00:00:00:00");
        readTime();
      }
      else if(opt == 2){ //2.-Seleccion juegos
        while(opt != 4){ //4.-Volver
          if(opt == 1){ // 1.-Contraseña
            
          }
          else if(opt == 2){ //2.-Cables
            
          }
          else if(opt == 3){ //3.-Llaves NFC
            
          }
        }
      }
      else if(opt == 3){ //3.Bomba armada
      }
      else if(opt == 4){ //4.Otras opciones
      }
    }
  }
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
  char confMen[maxOpt][20] ={ "1.Tiempo",
                        {'2','.','C','o','n','t','r','a','s','e',(char)0xEE,'a'},//"2.Contrase0a", {"2.Contrase",(char)0xEE,"a"},
                        "3.Etc",
                        "4.Etc",
                        "5.Volver"};
  
                        
  int opt;
  do{
    opt = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Configuracion");
    drawBomb(17, 0);

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
