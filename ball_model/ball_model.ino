const int sonarEchoPin = 10;
const int sonarTrigPin = 9;
const int solenoidSignal = 8;
const int laserPin = A5;

const int laserThreshold = 200;
const int maxDistance = 10;
const int timeConstant = 500;

long duration;
int distance;
bool laserHit;
int count;

void setup() {
  pinMode(sonarTrigPin, OUTPUT); // Sets the sonarTrigPin as an Output
  pinMode(sonarEchoPin, INPUT); // Sets the sonarEchoPin as an Input
  pinMode(solenoidSignal, INPUT);
  pinMode(A5, INPUT);

  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  distance = sonarSignal();
  laserHit = analogRead(laserPin) > laserThreshold ? true : false;

  if (distance < maxDistance && laserHit == true) { // instance of cup + laser hit
    count = 0;
    digitalWrite(solenoidSignal, HIGH); // RELEASE THE KRAKEN
    
    while (sonarSignal() < maxDistance && count < timeConstant) { // as long as cup is still there and we're not overtime, 
      delay(5);
      count++;
    }
    digitalWrite(solenoidSignal, LOW);
  }
}

// measure the sonar, get distance (we can change it from int for better resolution if you want
int sonarSignal() {
  digitalWrite(sonarTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonarTrigPin, LOW);
  duration = pulseIn(sonarEchoPin, HIGH);
  return duration * 0.034 / 2; // in cm
}
