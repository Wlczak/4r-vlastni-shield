
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  digitalWrite(D0, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
}
