// - Explosive
// In this game mode the bomb starts armed with the countdown to detonation already triggered. The
// game ends when the bomb is detonated, or when it is disarmed. If the accelerometer option is
// activated and movement is excessive pump will explode in 3 seconds.

void explosive() {
  unsigned long reloj = 0;
  String pass = "";
  bool bp = bPASS,
       bw = bWIRE,
       bk = bNFC;
  bool win = false;
  bool cuttedWire[4];
  for (int i = 0; i < 4; i++)
    cuttedWire[i] = boolRead(WIRE[i]);
  drawEmptyProgressBar(3);
  printActiveGames(bp, bw, bk, 0, true);
  int lastPercentage = 0;
  unsigned long game_counter = millis();
  while (reloj < RELOJ_BOMBA && !win) {
    //if(counter(reloj)){
    if (countMillis(10, game_counter)) {
      reloj++;
      showTime(RELOJ_BOMBA - reloj);
      int x = calculatePercentage(reloj, RELOJ_BOMBA);
      if(lastPercentage != x){
        drawPercentage(16, 3, x);
        int from = percentageBarPosition(lastPercentage, 30);
        int to = percentageBarPosition(x, 30);
        if(from != to) drawProgressBar(from, to, 30, 0, 3);
        lastPercentage = x;
      }
    }
    buzzing();
    if (reloj >= RELOJ_BOMBA) {
      reloj = RELOJ_BOMBA;
      drawPercentage(16, 3, 100);
      drawProgressBar(lastPercentage, 30, 30, 0, 3);
    }
    if (bp && checkPass(pass)) {
      bp = false;
      lcdBorra(0, 1, 19, 1);
      printActiveGames(bp, bw, bk, 0, true);
    }
    if (bw && checkWire(reloj, cuttedWire)) {
      bw = false;
      printActiveGames(bp, bw, bk, 0, true);
    }
    if (bk && checkNFC(reloj)) {
      bk = false;
      printActiveGames(bp, bw, bk, 0, true);
    }
    if (!bp && !bw && !bk && pushedButton(GREEN_BTN, false, 2)) win = true; // && green button pulsado
  }
  winMessage(win, 1);
  alarm(true);
}


