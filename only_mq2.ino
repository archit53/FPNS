void setup() {
  pinMode(A5, INPUT);
  Serial.begin(115200);
}
// vcc,gnd,A5
// MQ2.A0=ARDUINO.A5
void loop() {
  int analogSensor = analogRead(A5);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  
  delay(1000);
}
