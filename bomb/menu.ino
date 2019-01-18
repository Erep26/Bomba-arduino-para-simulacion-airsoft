int menu(){
  String MENU[] = {"Menu","1.-Iniciar juego","2.-Configuracion"};
  String MENU1[] = {"Modos de juego","1.-Bomba","2.-Dominacion"};
  String MENU2[] = {"1.-Tiempo", "2.-Seleccion juegos", "3.Bomba armada", "4.Otras opciones"};
  String MENU22[] = {String("1.-Contrase") + (char)0xEE + String("a"), "2.-Cables", "3.-Llaves NFC"};

  String MENU221[] = {String("Contrase") + (char)0xEE + String("a"), "1.-Si/No", String("2.-Cambiar") + String("Contrase") + (char)0xEE + String("a:"), String(PASS)};
  
  printMenu(MENU,3);
  drawBomb(17, 0);
  int opt = validOption(1, 2);
  if(opt == 1){ //1.-Iniciar juego
    while(opt != 0){//0.-Volver
      printMenu(MENU1,3);
      drawBomb(17, 0);
      opt = validOption(0, 2);
      switch(opt){
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
  else if(opt == 2){ // 2.-Configuracion
    while(opt != 0){//0.-Volver
      printMenu(MENU2,4);
      //drawBomb(17, 0);
      opt = validOption(0, 4);
      if(opt == 1){ //1.-Tiempo
        ld.clear();
        readTime();
      }
      else if(opt == 2){ //2.-Seleccion juegos
        while(opt != 0){ //4.-Volver
          printMenu(MENU22,3);
          opt = validOption(0, 3);
          if(opt == 1){ // 1.-Contraseña
            while(opt != 0){
              printMenu(MENU221,4);
              printYesNo(bPASS,1);
              opt = validOption(0, 2);
              if(opt == 1) bPASS = !bPASS;
              else if(opt == 2) newPass();
            }
            opt = -1;
          }
          else if(opt == 2){ //2.-Cables
            
          }
          else if(opt == 3){ //3.-Llaves NFC
            
          }
        }
        opt = -1;
      }
      else if(opt == 3){ //3.Bomba armada
      }
      else if(opt == 4){ //4.Otras opciones
      }
    }
    opt = -1;
  }
}

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
  for(int i = 0; i < n; i++){
    lcd.setCursor(0,i);
    lcd.print(m[i]);
  }
}

void lcdBorra(int col, int fil, int endCol, int endFil){
  for(int f = fil; f <= endFil; f++)
    for(int c = col; c <= endCol; c++){
      lcd.setCursor(c, f);
      lcd.print(" ");
    }
}

void readTime(){
  unsigned long h, m, s, cs;
  lcdBorra(0, 1, 16, 3);
  lcd.setCursor(0, 1);
  lcd.print("Introduce el tiempo:");
  lcd.setCursor(0, 2);
  lcd.print("00:00:00:00");
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

void printYesNo(bool yn, int fil){
  byte _S[] = { 0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E, 0x1F};
  byte _i[] = { 0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E, 0x1F};
  byte _N[] = { 0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x1F};
  byte _o[] = { 0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x1F};
  if(yn){
    lcd.createChar(0, _S);
    lcd.createChar(1, _i);
    lcd.setCursor(3, fil);
  }
  else{
    lcd.createChar(0, _N);
    lcd.createChar(1, _o);
    lcd.setCursor(6, fil);
  }
  lcd.write(0);
  lcd.write(1);
}

void newPass(){
  lcdBorra(0, 3, 19, 3);
  PASS = "";
  char key;
  for(int i = 0; i < 20; i++){
    key = keypad.waitForKey();
    if(key == '*' && i > 0){
      i--;
      lcd.setCursor(i, 3);
      lcd.print(" ");
    }
    else if(key == '#'){
      PASS[i] = '\0';
      i = 20;
    }
    else{
      PASS += key;
    }
  }
}

