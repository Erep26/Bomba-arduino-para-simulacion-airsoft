#define WIRE1 14
#define WIRE2 15
#define WIRE3 16
#define WIRE4 17
#define RED_BTN 18
#define GREEN_BTN 19

void setup() {
  pinMode(WIRE1, INPUT_PULLUP);
  pinMode(WIRE2, INPUT_PULLUP);
  pinMode(WIRE3, INPUT_PULLUP);
  pinMode(WIRE4, INPUT_PULLUP);
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(GREEN_BTN, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  Serial.print("WIRE1: ");
  Serial.println(digitalRead(WIRE1));
  Serial.print("WIRE2: ");
  Serial.println(digitalRead(WIRE2));
  Serial.print("WIRE3: ");
  Serial.println(digitalRead(WIRE3));
  Serial.print("WIRE4: ");
  Serial.println(digitalRead(WIRE4));
  Serial.print("RED_BTN: ");
  Serial.println(digitalRead(RED_BTN));
  Serial.print("GREEN_BTN: ");
  Serial.println(digitalRead(GREEN_BTN));
  Serial.println(" ");
  Serial.println(" ");

  delay(5000);
}
