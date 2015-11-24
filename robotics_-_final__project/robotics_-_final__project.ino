#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

// motor object
RedBotMotors motor;

//sensor variables, left right and middle
RedBotSensor lSen = RedBotSensor(A0);
RedBotSensor mSen = RedBotSensor(A6);
RedBotSensor rSen = RedBotSensor(A7);

// LED pin
int LED = 13;

//sonar pins

//front pins
int frontTrig = 9;
int frontEcho = 3;

//right pins
int rightTrig = 11;
int rightEcho = 10;


const int bgLevel = 600; // variable for gray
const int lineLevel = 700; // variable for black

// constants for speed
const int FAST = 130;  
const int MED = 100;
const int SLOW = 90;
int SPEED = MED;

bool lineFound;
int dist = checkDistance(rightTrig, rightEcho);


void setup() {
  
//turns led off
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);

//sets current speed to MED and values to 0

int ratio = 0;


// sets up the sonar sensors 
  Serial.begin(9600);
  pinMode(rightTrig, OUTPUT);
  pinMode(rightEcho, INPUT);
   pinMode(frontTrig, OUTPUT);
  pinMode(frontEcho, INPUT);
}

void loop()
{ 
  while(checkSensors() < 550){
    followWall();
  }

  leftAngle(530);
  driveStraight(SPEED, 160);
  driveStraight(120, 960);
  
  
 
  

}

void followWall(){
  
  delayCheck(50);
  float newDist = checkDistance(rightTrig, rightEcho);
  float diff = newDist / dist;
  float front = checkDistance(frontTrig, frontEcho);

  if(front < 5 && newDist > 8){
    leftAngle(250);
    driveStraight(SPEED, 260);

    if(front < 10 && newDist > 10){
      leftAngle(150);
    driveStraight(SPEED, 60);
    }
    
  }

  if(front < 6 && newDist > 20){
    rightAngle(750);
    driveStraight(SPEED, 1360);
    leftAngle(650);
    driveStraight(SPEED*2, 1860);
  }
  if(front < newDist && newDist > 10){
    leftAngle(87);
    driveStraight(SPEED, 300);
  }
  if(newDist < 5){
    leftAngle(30);
    driveStraight(SPEED, 200);
  }
  
  if(newDist > 8 && newDist < 14){
    rightAngle(20);
    driveStraight(SPEED, 60);
  }
  if(newDist > 20){
    rightAngle(450);
    driveStraight(SPEED, 760);
    leftAngle(150);
  }

  driveStraight(SPEED, 190);
  

    dist = newDist;
}



// prints vales of sonar and light sensors
void printSensors(){
  
  Serial.println(checkDistance(frontTrig, frontEcho));
  delay(500);
  Serial.println(checkDistance(rightTrig, rightEcho));
  delay(500);
  Serial.println(checkSensors());
  delay(500);

}

float checkDistance(int trigPin, int echoPin){
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  
  //send sonar pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  //clear trigger
  digitalWrite(trigPin, LOW);
  
  //calculates dist
  float duration = pulseIn(echoPin, HIGH);
  
  //convert
  float distance = duration / 58;
  
  return distance;
  
}

//drives forward based on int input

void driveStraight(int speed, int time){
  
  motor.drive(speed); 
  delay(time);
  motor.brake();
  delay(time);
  
}

// turns at a leftt angle when input at 650
void leftAngle(int angle){
   motor.leftDrive(-70);  
   motor.rightDrive(67); 
   delay(angle);
   motor.brake();
}

// turns at a right angle when input at 650
void rightAngle(int angle){
   motor.leftDrive(67);  
   motor.rightDrive(-67); 
   delay(angle);
   motor.brake();
}

void lineFollow(){




  
}


// combines the delay function with the check function
void delayCheck(int time){
  
  for(int i = 0; i < time; i ++){
    if(lineFound == false){
      delay(1);
      if(checkSensors() > 500) foundLine = true;
    }else{
      lineFollow();
    }
   }
  }

// takes th average of the 3 sensors and rreturns it as a float
float checkSensors(){
  
   float average = ((lSen.read() + mSen.read() + rSen.read() ) /3);

   return average;
  
}






