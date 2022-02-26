// Constants

  // input pin for PIR sensor
  int PIRiPin = 13; 
     
  // current state of PIR sensor           
  int pirState = LOW;
  
  // value returned by PIR sensor             
  int motion = 0; 
  
  // trigger and echo pins for front ultrasonic sensors
  const int trigFL = 2; 
  const int echoFL = 3;
  const int trigFR = 4;
  const int echoFR = 5;

  // trigger and echo pins for side ultrasonic sensors
  const int trigSL = 7; 
  const int echoSL = 6;
  const int trigSR = 8;
  const int echoSR = 9;
  
  // constant for conversion
  const float speed_sound = .0343;

  // maximum distance to person
  const float max_dist = 50;

  // time interval between measurements
  int interval = 1000;
  
  // store time and distance for front ultrasonic sensors
  float timeFL, distFL, timeFR, distFR;

  // store time and distance for side ultrasonic sensors
  float timeSL, distSL, timeSR, distSR;

void setup() {
  // set pin mode for each pin
  pinMode(PIRiPin, INPUT);
  pinMode(trigFL, OUTPUT); 
  pinMode(echoFL, INPUT); 
  pinMode(trigFR, OUTPUT); 
  pinMode(echoFR, INPUT); 
  pinMode(trigSL, OUTPUT); 
  pinMode(echoSL, INPUT); 
  pinMode(trigSR, OUTPUT); 
  pinMode(echoSR, INPUT);
  Serial.begin(9600);  
}

void loop() {

// DATA COLLECTION

  // calculate distance from front right US
  digitalWrite(trigFR, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigFR, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigFR, LOW); 
  // finds duration of pulse
  timeFR = pulseIn(echoFR, HIGH); 
  // distance = speed * (time / 2)
  distFR = (timeFR*speed_sound)/2; 


  // calculate distance from front left US 
  delayMicroseconds(2);
  digitalWrite(trigFL, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigFL, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigFL, LOW); 
  // finds duration of pulse
  timeFL = pulseIn(echoFL, HIGH);
  // distance = speed * (time / 2)
  distFL = (timeFL*speed_sound)/2;

  // calculate distance from right, side US
  digitalWrite(trigSR, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigSR, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigSR, LOW); 
  // Finds duration of pulse
  timeSR = pulseIn(echoSR, HIGH); 
  // Distance = speed * (time / 2)
  distSR = (timeSR*speed_sound)/2; 

  delayMicroseconds(2);
  // Sends 8 microsecond pulse for left
  digitalWrite(trigSL, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigSL, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigSL, LOW); 

  // Finds duration of pulse
  timeSL = pulseIn(echoSL, HIGH);
  // Distance = speed * (time / 2)
  distSL = (timeSL*speed_sound)/2;

  // detect motion from PIR sensor
  motion = digitalRead(PIRiPin);

// DEBUGGING AND OUTPUT

  // debugging for front ultrasonic sensors
  if (distFR > max_dist && distFR > max_dist) {
    Serial.println("No object detected in front");
  }
  else if (distFL > max_dist) {
    Serial.println("Turn right");
  }
  else if (distFR > max_dist) {
    Serial.println("Turn left");
  }
  else {
    Serial.println("Continue");
  }

  // output for side ultrasonic sensors
  Serial.print("Distance (Right): ");
  Serial.println(distSR);
  Serial.print("Distance (Left): ");
  Serial.println(distSL);

  // debugging for PIR sensor
  if (motion == HIGH) {            
      if (pirState == LOW) {
        // we have just turned on
        Serial.println("Motion detected!");
        pirState = HIGH;
      }
  } 
  else {
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  // time between measurements
  delay(interval);
}
