//logic: if both sensors are pointing towards the same object approach
// if not, turn to match sensors

#include <Servo.h>
#include<NewPing.h>


// NOTE : YOUR VARIABLE DEFINTIONS ALL OVER THE PLACEEEE
// need: pins for each sensor and motor pins 
// have not tested yet


// define which pins match the tigger and echo, I just have values here rn
#define trigD1 9
#define echoD1 8
#define trigD2 7
#define echoD2 6
#define maxdistance 300

Newping sonar(int trigPin, int echoPin, maxdistance)

///possible error here

//intialize servo and position
Servo myservo;
int pos = 0;
long time;

float duration , distance

void setup(){
  myservo.attach(10)

  pinMode(trigD1, OUTPUT);
  pinMode(echoD1, INPUT);
  pinMode(trigD2, OUTPUT);
  pinMode(echoD2, INPUT);

  myservo1.write(100);
  Serial.begin(9600);
}


void loop() {

  //distance form duration
  //343 meteres per sec
  duration = sonar.ping(trigD1,echoD1);
  distance1 = (duration/2)*0.0343;

  duration2= sonar.ping(trigD2, echoD2);
  distance2 = (duration2/2)*0.0343;



  //get distances and stuffs

  //check if out of bounds


  if (distance1 >= 300 || distance1 < 0){
    distance1 = 0;
  }

  if (distance2 >= 300 || distance2 < 0){
    distance2 = 0;
  }


//check difference between motors 
  difference = (distance1-distance2);
  absDiff = abs(difference);

  if (distance 1 == 0  && distance 2 == 0 ){
    lookRight():
    lookLeft();
  }


while (difference <35) {
  moveForward();
}

//if distance 2 is right
if(distance2>=distance1)
  {
    turnRight();
}else{
  moveForward();
}

//if distance 1 is left
if(distance1>=distance2)
  {
    turnLeft();
}else{
  moveForward();
}




  ///this is for avoidance protocals : i.e the side sensros

//  duration3 = sonar.ping(trigD1,echoD1);
//  distance3 = (duration/3)*0.0343;

//  duration4= sonar.ping(trigD2, echoD2);
//  distance4 = (duration4/2)*0.0343;

//if dis  int distance = getDistance();                   //Check that there are no objects ahead
//  if(distance >= stopDist)                        //If there are no objects within the stopping distance, move forward
//  {
//    moveForward();
//  }
//  while(distance >= stopDist)                     //Keep checking the object distance until it is within the minimum stopping distance
///  {
//    distance = getDistance();
//    delay(250);
//  }
//  stopMove();                                     //Stop the motors
//  int turnDir = checkDirection();                 //Check the left and right object distances and get the turning instruction
//  Serial.print(turnDir);
//  switch (turnDir)                                //Turn left, turn around or turn right depending on the instruction
//  {
//    case 0:                                       //Turn left
//     turnLeft (400);
//      break;
//    case 1:                                       //Turn around
//      turnLeft (700);
//      break;
//    case 2:                                       //Turn right
//      turnRight (400);
//      break;
//  }
//}


/



int lookRight()
{
    myservo.write(50);
    delay(100);
    //int distance = readPing();
    delay(100);
    myservo.write(115);
    //return distance;
}

int lookLeft()
{
    myservo.write(170);
    delay(100);
    //int distance = readPing();
    delay(100);
    myservo.write(115);
  //  return distance;
    delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}



///get sonar function
void NewPing sonar(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}


void moveForward()                            //Set all motors to run forward
{
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
}

void moveForwardb() {

   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}




int getDistance()                                   //Measure the distance to an object
{
  unsigned long pulseTime;                          //Create a variable to store the pulse travel time
  int distance;                                     //Create a variable to store the calculated distance
  digitalWrite(trig, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pulseTime = pulseIn(echo, HIGH, timeOut);         //Measure the time for the pulse to return
  distance = (float)pulseTime * 340 / 2 / 10000;    //Calculate the object distance based on the pulse time
  return distance;
}
