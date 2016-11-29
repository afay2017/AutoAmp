
#include <Servo.h>

int masterPotPin = A2;
int slavePotPin  = A3;

int masterPot;
int slavePot;

int leftPin  = 28;
int rightPin = 29;

int val;


Servo myservo;  // create servo object to control a servo


void setup() {
   Serial.begin(9600);
   pinMode(leftPin,  OUTPUT);
   pinMode(rightPin, OUTPUT);
    myservo.attach(7);
}

void loop() {

  int masterPot = analogRead(masterPotPin);
  int slavePot  = analogRead(slavePotPin);

  
 if (masterPot + 10 < slavePot){
   digitalWrite(leftPin, HIGH);
   digitalWrite(rightPin, LOW);
   Serial.println(1);
 } else if (masterPot - 10> slavePot){
   digitalWrite(leftPin, LOW);
   digitalWrite(rightPin, HIGH);
   Serial.println(2);
 } else {
   digitalWrite(leftPin, LOW);
   digitalWrite(rightPin, LOW);
 }

 
   val = map(masterPot, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
   myservo.write(val);                  // sets the servo position according to the scaled value



}
