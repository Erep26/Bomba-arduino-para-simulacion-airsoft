//  Funciones que manejan la lectura y escritura de tarjetas NFC
int blockNumber = 2;
int trailerBlock = (blockNumber / 4 * 4) + 3;

void writeNFC(byte data[]) {
  MFRC522::StatusCode status;
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &nfcKey, &(mfrc522.uid));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockNumber, data, 16);
}
void readNFC(byte data[]) {
  MFRC522::StatusCode status;
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &nfcKey, &(mfrc522.uid));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockNumber, data, 18);
}

void mfr_halt() {
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void waitForNewNFC() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(NFC_CARD_ON_READER);
  while ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial());
  pita();
}
