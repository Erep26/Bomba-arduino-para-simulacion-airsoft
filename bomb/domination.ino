// - Domination
// In this mode the device acts as a station or base. When game time cowntdown starts, base is in
// neutral position. The objective for both teams is to capture the base, starting to add time on behalf
// of capturing team. Once the base is captured, it starts to add minutes to the “owner” team and
// subtracting minutes from the opposing team until both times become equal, from that pointon it
// stops subtracting minutes from opposing team. If the base is in neutral position does not adds not
// substract time for any team. If you have activated accelerometer and if the movement is excessive,
// the base switches to neutral automaticly.
void domination() {
  long reloj = 0;
  long points[2] = {0, 0};
  bool dominator[2] = {false, false};

  lcd.setCursor(0, 0);
  lcd.print(RED_TEAM);
  lcd.print("  ");
  lcd.print(GREEN_TEAM);
  lcd.setCursor(0, 1);
  lcd.print("000000    000000");



  long game_counter = millis();
  drawEmptyProgressBar(2);
  int millisCounter = 0;
  while (reloj < RELOJ_JUEGO) {

    if (countMillis(10, game_counter)) {
      reloj++;
      millisCounter++;
      if (millisCounter == 10) { //359999 max puntos
        millisCounter = 0;
        if (dominator[0]) {
          points[0]++;
          int i = 0;
          for (long p = points[0]; p > 0; p /= 10) i++;
          lcd.setCursor(6 - i, 1);
          lcd.print(points[0]);
        }
        if (dominator[1]) {
          points[1]++;
          int i = 0;
          for (long p = points[1]; p > 0; p /= 10) i++;
          lcd.setCursor(16 - i, 1);
          lcd.print(points[1]);
        }
      }
      int x = calculatePercentage(reloj, RELOJ_JUEGO);
      showTime(RELOJ_JUEGO - reloj);
      drawProgressBar(x, 2);
    }
    buzzing();
    if (dominator[0]) {
      if (pushedButton(GREEN_BTN, false, 3)) dominator[0] = false;
    }
    if (dominator[1]) {
      if (pushedButton(RED_BTN, false, 3)) dominator[1] = false;
    }
    if (!dominator[0] && !dominator[1]) {
      if (boolRead(GREEN_BTN) && pushedButton(RED_BTN, false, 3)) dominator[0] = true;
      if (boolRead(RED_BTN) && pushedButton(GREEN_BTN, false, 3)) dominator[1] = true;
    }
  }
  if (points[0] == points[1]) {
    lcd.setCursor(0, 3);
    lcd.print(DRAW);
  }
  else winMessage((points[1] > points[0]), 0);
}
