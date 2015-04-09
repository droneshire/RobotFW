void setup() {
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  digitalWrite(5, HIGH);  //enable driver
}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(2000);
  digitalWrite(13, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(2000);

}
