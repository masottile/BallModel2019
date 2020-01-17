
const int SENSOR = A1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT);
  
  Serial.begin(9600);
  Serial.print("Sensor Value:");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);

  double val = analogRead(SENSOR);
  
  Serial.print(val);
  Serial.print("\n");
}
