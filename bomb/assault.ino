// - Assault
// Bomb has to be defended by team ALFA (blue) during Game Time. Attacking team, BRAVO
// tem(red) objective is to arm the bomb and once armed must defend int until detonation, preventing
// Alpha team to defuse it. The bomb can be armed and defused many times as the game time allows.
// As an added game difficulty, the introduction of a code may be necessary to arm and disarm the
// bomb.
// Bomba puede armarse y desarmarse hasta que acabe el tiempo de juego

void assault() {
  unsigned long relojBomba = 0;
  unsigned long relojJuego = 0;
  String pass = "";
  bool bp = bPASS,
       bk = bNFC;
  bool bombActive = false;
  drawEmptyProgressBar(2);
  printActiveGames(bp, false, bk, 0, true);
  lcd.setCursor(0, 1);
  lcd.print(BOMB_UNACTIVE);
  int lastPercentage = 0;
  unsigned long game_counter = millis();
  while ( relojBomba < RELOJ_BOMBA && relojJuego < RELOJ_JUEGO) {
    buzzing();
    //--------------Contador juego----------------
    if (countMillis(10, game_counter)) {
      relojJuego++;
      if (bombActive) {
        relojBomba++;
        showTime(RELOJ_BOMBA - relojBomba);
        int x = calculatePercentage(relojBomba, RELOJ_BOMBA);
        if (lastPercentage != x) {
          drawPercentage(16, 2, x);
          int from = percentageBarPosition(lastPercentage, 30);
          int to = percentageBarPosition(x, 30);
          if (from != to) drawProgressBar(from, to, 30, 0, 2);
          lastPercentage = x;
        }
      }
      else showTime(RELOJ_JUEGO - relojJuego);
    }
    //-------------Chequeo protecciones activas--------------------------
    if (bp && checkPass(pass)) {
      bp = false;
      printActiveGames(bp, false, bk, 0, bombActive);
      lcdBorra(0, 1, 19, 1);
      lcd.setCursor(0, 1);
      if (bombActive) lcd.print(BOMB_ACTIVE);
      else lcd.print(BOMB_UNACTIVE);
    }
    if (bk && checkNFC(relojBomba)) {
      bk = false;
      printActiveGames(bp, false, bk, 0, bombActive);
    }
    //--------------------------------------------------------------------
    //--------------Activacion/desactivacion bomba-----------------------
    if (!bombActive && !bp && !bk && pushedButton(RED_BTN, false, 3)) {
      bombActive = true;
      bp = bPASS;
      bk = bNFC;
      printActiveGames(bp, false, bk, 0, false);
      lcdBorra(0, 1, 19, 1);
      lcdBorra(0, 3, 19, 3);
      lcd.setCursor(0, 1);
      lcd.print(BOMB_ACTIVE);
    }
    else if (bombActive && !bp && !bk && pushedButton(GREEN_BTN, false, 3)) {
      bombActive = false;
      bp = bPASS;
      bk = bNFC;
      printActiveGames(bp, false, bk, 0, true);
      lcdBorra(0, 3, 19, 3);
      lcdBorra(0, 3, 19, 3);
      lcd.setCursor(0, 1);
      lcd.print(BOMB_UNACTIVE);
    }
  }
  winMessage(!bombActive, 0);
  alarm(true);
}

