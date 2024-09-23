void IRAM_ATTR pain() {
  Serial.println(digitalRead(D6));
  Serial.println(digitalRead(D7));
  Serial.println("digitalRead(D6)");
}
void IRAM_ATTR pain2() {
  Serial.println(digitalRead(D5));
  Serial.println("digitalRead(D5)");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(D6), pain, CHANGE);
  attachInterrupt(digitalPinToInterrupt(D5), pain2, CHANGE);
  digitalWrite(D0, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D3, LOW);
  delay(500);
  digitalWrite(D3, HIGH);
  delay(500);
}
