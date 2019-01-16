void dommination(){
}

int game(){
  unsigned long reloj = RELOJ;
  String pass = "";
  drawEmptyProgressBar();
  while(!ENDGAME){
    counter(reloj);
    buzzing();
    percentageBomb(reloj);
    if(readChar(pass) && PASS == pass){
      ENDGAME = true;
      WIN =true;
    }
  }

  keypad.setHoldTime(5000);
/*
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Pulsa * durante 5s");
  lcd.setCursor(0, 2);
  lcd.print("para resetear");
  lcd.setCursor(0, 3);
  lcd.print("el dispositivo");*/
  
  while(ENDGAME){//fin juego
    if(WIN){
      lcd.setCursor(0, 0);
      lcd.print("Bomba desactivada");
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print("La bomba a explotado");
    }
    char key = keypad.getKey();
    if(keypad.getState() == HOLD && key == '*') while(1)lcd.clear();
  }
}

void counter(unsigned long &reloj){
  int time = millis();
  if(time - TIME >= 10){
    TIME = time;
    reloj--;
    showTime(reloj);
    tone(BUZZPIN, 2400, 10);
  }
  if(reloj == 0) ENDGAME = true;
}

void percentageBomb(unsigned long reloj){
  byte bar10[] = {0x0F, 0x18, 0x13, 0x17, 0x17, 0x13, 0x18, 0x0F}; //punta izquierda llena
  byte bar11[] = {0x1F, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x1F}; //centro mitad
  byte bar12[] = {0x1F, 0x00, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x1F}; //centro lleno
  byte bar13[] = {0x1E, 0x03, 0x19, 0x1D, 0x1D, 0x19, 0x03, 0x1E}; //punta derecha llena
  
  lcd.createChar(3, bar10);
  lcd.createChar(4, bar11);
  lcd.createChar(5, bar12);
  lcd.createChar(6, bar13);
  
  int x = (((reloj * 100)/RELOJ) * -1) + 100;
  lcd.setCursor(0, 2);
  lcd.print(x);
  lcd.print("%");
  x = int((float(x)/100)*20);
  for(int i = 1; i < x; i++)
  {
    lcd.setCursor(i-1, 3);
    if(i == 1) lcd.write(3);
    if(i > 1 && i < 20) lcd.write(5);
    if(i == 20) lcd.write(6);
  }
}

void drawEmptyProgressBar(){
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
  for(int i = 1; i < 19; i++){
    lcd.setCursor(i, 3);
    lcd.write(1);
  }
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
  
  if(millis()/500%2) ld.setBright(1);
  else ld.setBright(15);
}


bool readChar(String p){
  char key = keypad.getKey();
  if(key){
    switch(key){
      case '#':
        return true;
        break;
      case '*':
        p = "";
        break;
      default:
        p += key;
        break;
    }
  }
  return false;
}

unsigned long timeBuzzing = millis();
void buzzing(){
  //if(millis()/1000%2) tone(BUZZPIN, 2400, 10);
}

