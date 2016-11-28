
int masterPotPin = A3;
int slavePotPin  = A4;

int masterPot;
int slavePot;

int leftPin  = 28;
int rightPin = 29;

void setup() {
   Serial.begin(9600);
   pinMode(leftPin,  OUTPUT);
   pinMode(rightPin, OUTPUT);
}

void loop() {

  int masterPot = analogRead(masterPotPin);
  int slavePot  = analogRead(slavePotPin);

  
 if (masterPot > slavePot){
   digitalWrite(leftPin, HIGH);
   digitalWrite(rightPin, LOW);
 } else if (masterPot < slavePot){
   digitalWrite(leftPin, HIGH);
   digitalWrite(rightPin, LOW);
 }


}
