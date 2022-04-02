//#include <bits/stdc++.h>
using namespace std;

// Constants

  // input pin for PIR sensor
  int PIRPin = 10;

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


  //pins for motors

  //Motor A

int enA = 11;
int in1 = 13;
int in2 = 12;

//Motor B

int enB = 3;
int in3 = 5;
int in4 = 6;

  //pin for LED
  #define LEDPin 13

  //////////// Variables

  // store time and distance for front ultrasonic sensors
  float timeFL, distFL, timeFR, distFR;

  // store time and distance for side ultrasonic sensors
  float timeSL, distSL, timeSR, distSR;

  // store difference between two sensor values
  float diffS, absDiffS;

  //PIR sensor
  int see_val;

///////----- function declarations

void Lost_sequence();




void setup() {

     // Set all the motor control pins to outputs
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);



  // set pin mode for each pin
  pinMode(PIRPin, INPUT);
  pinMode(trigFL, OUTPUT);
  pinMode(echoFL, INPUT);
  pinMode(trigFR, OUTPUT);
  pinMode(echoFR, INPUT);
  pinMode(trigSL, OUTPUT);
  pinMode(echoSL, INPUT);
  pinMode(trigSR, OUTPUT);
  pinMode(echoSR, INPUT);

  // LED Pin
  pinMode(LEDPin,OUTPUT);
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
  motion = digitalRead(PIRPin);

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




  //////////////////////////////////////////////////////////////////////////////
  // FOLLOWING LOGIC

  // the goal is for the front sensors the keep the person an equal distance
  // the side sensors only need to noitfy when following will result in bumping

  //declare : diffS , absDiffS,


  //check the difference between two sensor readings
  diffS = (distSR-distSL);
  absDiffS = abs(diffS);


  //lost sequence

  //if the sensors indicate 0 or out of range, notify

  if (distFR == 0  && distFL == 0 ) {
    Lost_sequence();
    lost();
  }


  // i could make notification a light going off

  //    Lost();
  //    Right();
  //    Left();
  //  Serial.print("WYAAA ");
  //   if (see_val = 1){
  //       One();
   //      Serial.print("forwarddd cuz see ");
  //    }
  // }

  //else if (distSR > max_dist && distSL > max_dist){
    //Serial.print("WYAAA??? ");




  //if ony one senson can "see"


    //while the difference betwwen the sensors is *sufficiently* small, move forward
    while (diffS <=15) {
      One();
      // keep time using millis or use some counter?
    Serial.print("forwarddd ");
    }

    //if distance to the right sensor is greater, left turn to get values equal
    if(distFR>distFL)
    {
     Left();
    Serial.print("go left ");
  }else{
    One();
    Serial.print("forwarddd after left ");
    }

    //if distance to left sensor is greater, right turn to get values equal
   if(distFL>distFR)
   {
     Right();
    Serial.print("go right ");
  }else{
  //moveForward();
  Serial.print("forward after right ");
  }



  // if the sensed object's value is not close to the average distance value ignore
  // this only engages after the car has been following something for some time
  //
  // time_now = millis()/1000
  // seconds = time_now - time_last
  //
  // if(seconds > 3){
  //   if dist FL or dist FR > double of median distance or signficant percentage{
  //     Lost_sequence()
  //
  //     // make array of dist values
  //     // find median of unsorted array
  //     //
  //   }
  // }





  /////////////////////////////////////

  ///AVOIDANCE LOGIC

  //if there's an obstacle on the left but not right
  // move back, go right , then look for person
  if (distSL < 25 & distSR > 25) {
    Back();
    delay(50);
    Right();
    delay(50);
    //lost sequence to tell owner come back
    Lost_sequence();
    lost();
  }

  if (distSR < 25 & distSL > 25) {
    Back();
    delay(50);
    Left();
    delay(50);
    //lost sequence to tell owner come back
    Lost_sequence();
    lost();
  }

}



////////////////
///Logic Functions




void Lost_sequence()
{
    //blink LED
    for (int i = 0; i < 6; i++){
      digitalWrite(LEDPin,HIGH); //Turn the LED on
    }
    // drive forward and back
    One();
    Back();
  }

   int lost(){

    see_val = digitalRead(PIRPin); // read input value

    if (see_val == HIGH) { // check if the input is HIGH
      digitalWrite(LEDPin, HIGH); // turn LED ON

    if (pirState == LOW) {
    // we have just turned on
      Serial.println("Motion detected!");
    // We only want to print on the output change, not state
    pirState = HIGH;
    }

    } else {

    delayMicroseconds(100);
    digitalWrite(LEDPin, LOW); // turn LED OFF

  }


    if (pirState == HIGH){
    // we have just turned of
    Serial.println("Motion ended!");
    // We only want to print on the output change, not state
    pirState = LOW;
    }
     see_val = digitalRead(PIRPin);

    return see_val;

    }





  ///////////////////////////////////////////
  ////MOTOR CONTROL







  void One()
  {
    // this function will run motors in one direction at fied speed

    //Turn on motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    analogWrite(enA,50);
    delayMicroseconds(10);
    analogWrite(enA,100);
    delayMicroseconds(10);
    analogWrite(enA,150);
    delayMicroseconds(10);
    analogWrite(enA,200);


    //Turn on motor B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);


    analogWrite(enB,50);
    delayMicroseconds(10);
    analogWrite(enB,100);
    delayMicroseconds(10);
    analogWrite(enB,150);
    delayMicroseconds(10);
    analogWrite(enB,200);
  }

  void Back()
  {
    // this function will run motors in one direction at fied speed

    //Turn on motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    analogWrite(enA,50);
    delayMicroseconds(10);
    analogWrite(enA,100);
    delayMicroseconds(10);
    analogWrite(enA,150);
    delayMicroseconds(10);
    analogWrite(enA,200);


    //Turn on motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);


    analogWrite(enB,50);
    delayMicroseconds(10);
    analogWrite(enB,100);
    delayMicroseconds(10);
    analogWrite(enB,150);
    delayMicroseconds(10);
    analogWrite(enB,200);
  }

  void Right()
  {
    // this function will run motors in opposite direction at fied speed

    //Turn on motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    analogWrite(enA,50);
    delayMicroseconds(10);
    analogWrite(enA,100);
    delayMicroseconds(10);
    analogWrite(enA,150);
    delayMicroseconds(10);
    analogWrite(enA,200);


    //Turn on motor B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);


    analogWrite(enB,50);
    delayMicroseconds(10);
    analogWrite(enB,100);
    delayMicroseconds(10);
    analogWrite(enB,150);
    delayMicroseconds(10);
    analogWrite(enB,200);
  }

  void Left()
  {
    // this function will run motors in opposite direction at fixed speed

    //Turn on motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    analogWrite(enA,50);
    delayMicroseconds(10);
    analogWrite(enA,100);
    delayMicroseconds(10);
    analogWrite(enA,150);
    delayMicroseconds(10);
    analogWrite(enA,200);


    //Turn on motor B
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);


    analogWrite(enB,50);
    delayMicroseconds(10);
    analogWrite(enB,100);
    delayMicroseconds(10);
    analogWrite(enB,150);
    delayMicroseconds(10);
    analogWrite(enB,200);
  }








  //
  // // Function for calculating
  // // the median
  // double findMedian(vector<int> a,
  //                   int n)
  // {
  //
  //     // If size of the arr[] is even
  //     if (n % 2 == 0) {
  //
  //         // Applying nth_element
  //         // on n/2th index
  //         nth_element(a.begin(),
  //                     a.begin() + n / 2,
  //                     a.end());
  //
  //         // Applying nth_element
  //         // on (n-1)/2 th index
  //         nth_element(a.begin(),
  //                     a.begin() + (n - 1) / 2,
  //                     a.end());
  //
  //         // Find the average of value at
  //         // index N/2 and (N-1)/2
  //         return (double)(a[(n - 1) / 2]
  //                         + a[n / 2])
  //                / 2.0;
  //     }
  //
  //     // If size of the arr[] is odd
  //     else {
  //
  //         // Applying nth_element
  //         // on n/2
  //         nth_element(a.begin(),
  //                     a.begin() + n / 2,
  //                     a.end());
  //
  //         // Value at index (N/2)th
  //         // is the median
  //         return (double)a[n / 2];
  //     }
  // }
  //
