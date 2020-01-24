const int sonarEchoPin = 11;
const int sonarTrigPin = 9;
const int solenoidSignal = 6;
const int laserPin = A5;

const int laserThreshold = 5;
const int maxDistance = 100;
const int timeConstant = 600;

long duration;
int distance;
bool laserHit;
int count;

void setup() {
  pinMode(sonarTrigPin, OUTPUT); // Sets the sonarTrigPin as an Output
  pinMode(sonarEchoPin, INPUT); // Sets the sonarEchoPin as an Input
  pinMode(solenoidSignal, OUTPUT); // Output pin for signal to relay
  pinMode(A5, INPUT); // Analog input from laser 

  digitalWrite(solenoidSignal, LOW); // make sure that valve is closed
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  
  digitalWrite(solenoidSignal, LOW); // make sure that valve is closed
  distance = sonarSignal(); 
  laserHit = analogRead(laserPin) > laserThreshold ? true : false;

  if (distance < maxDistance && laserHit == true) { // instance of triggering
    count = 0;
    digitalWrite(solenoidSignal, HIGH); 
    Serial.println("We're on!"); 
    
    while (sonarSignal() < maxDistance && count < timeConstant) { // as long as cup is still there + time hasnt't been too long
      Serial.println("Still goin'"); 
      delay(5);
      count++;
    }

    Serial.println("Done!");
    digitalWrite(solenoidSignal, LOW); // close valve
    delay(15000); // wait a while to start looking again
    Serial.println("Starting over!");
/*
    while(sonarSignal() < maxDistance){
      Serial.println("WE ARE IN THE LOOP!");
      delay(5);
    }*/
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
  return duration * 0.34/2; // in mm
}
