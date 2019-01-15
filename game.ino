int game(){
  unsigned long reloj = RELOJ;
  drawEmptyProgressBar();
  while(!ENDGAME){
    counter(reloj);
    percentageBomb(reloj);
    if(readChar() && PASS == pass){
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

