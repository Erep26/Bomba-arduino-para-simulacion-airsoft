// - Counterstrike
// There are three ways to finish the game.
// Game time passes away and BRAVO team (red) has not succeeded in placing and arming device,
// ALPHA team wins (blue).
// BRAVO team is able to place and arm the bomb, but can not prevent ALFA team from disarming it.
// ALPHA team (blue) wins.
// BRAVO team is able to place and arm the bomb and ALPHA team fails in disarming it so the bomb
// detonates. BRAVO team wins ( red).
// As a recommendation for balancing team options the place or places where the bomb should be
// placed should be half way for both teams to avoid defenders take too advantadge positions.
// As an added element of difficulty for terrorists, there is an accelerometer in the bomb (activated or
// not through the configuration "accelerometer" menu) that cause premature activation in case of
// excessive movement.
// As an added element of difficulty to the counter terrorist unit, deactivation pasword may be required
// to defuse bomb (can be activated in the options menu Configuration "encryption" and "CODE") 5
// digits.
// To facilitate the transport, anchors are added to add a 2-point sling. (sling not included)
//
// Se arma y desarma 1 sola vez
void counterstrike() {
  unsigned long relojBomba = 0;
  unsigned long relojJuego = 0;
  String pass = "";
  bool bp = bPASS,
       bk = bNFC;
  bool win = false;
  bool bombActive = false;

  printActiveGames(bp, false, bk, 0, false);
  int lastPercentage = 0;
  unsigned long game_counter = millis();
  while (relojJuego < RELOJ_JUEGO && !bombActive) {
    if (countMillis(10, game_counter)) {
      relojJuego++;
      showTime(RELOJ_JUEGO - relojJuego);
    }
    if (bp && checkPass(pass)) {
      bp = false;
      printActiveGames(bp, false, bk, 0, false);
    }
    if (bk && checkNFC(relojBomba)) {
      bk = false;
      printActiveGames(bp, false, bk, 0, false);
    }
    if (!bp && !bk && pushedButton(RED_BTN, false, 3)) bombActive = true;
    buzzing();
  }
  if (relojJuego < RELOJ_JUEGO) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(BOMB_ACTIVE);
    delay(1000);
    lcd.clear();
    bp = bPASS;
    bk = bNFC;
    drawEmptyProgressBar(2);
    printActiveGames(bp, false, bk, 0, true);
    game_counter = millis();
    while (relojBomba < RELOJ_BOMBA && !win) {
      if (countMillis(10, game_counter)) {
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
      buzzing();
      if (relojBomba >= RELOJ_BOMBA) {
        relojBomba = RELOJ_BOMBA;
        drawProgressBar(lastPercentage, 30, 30, 0, 2);
      }
      if (bp && checkPass(pass)) {
        bp = false;
        lcdBorra(0, 1, 19, 1);
        printActiveGames(bp, false, bk, 0, true);
      }
      if (bk && checkNFC(relojBomba)) {
        bk = false;
        printActiveGames(bp, false, bk, 0, true);
      }
      if (!bp && !bk && pushedButton(GREEN_BTN, false, 3)) { // && green button pulsado
        win = true;
      }
    }
  }
  winMessage(win, 1);
  alarm(true);
}

