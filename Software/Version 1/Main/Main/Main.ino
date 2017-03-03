    #include <Arduino.h>
    #include <AmpChannel.cpp>

AmpChannel curChannel;

void setup() {
  // put your setup code here, to run once:
  curChannel = new AmpChannel((int)1);

  pinMode(1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void applyPins(){
  digitalWrite(curChannel.bypassPin,curChannel.getBypassInt());
  switch (curChannel.getHead()){
    case curChannel.ORANGE:
    digitalWrite(curChannel.headPin, LOW);
    break;

    case curChannel.CRUNCH:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, LOW);
    break;

    case curChannel.LEAD:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, HIGH);
    break;
  }

  digitalWrite(curChannel.headEffectsPin,curChannel.getHeadEffects());
  digitalWrite(curChannel.mesaEffectsPin,curChannel.getMesaEffects());

  applyMesaChannelPins(curChannel.getAmpChannelNumber());

}

void applyMesaChannelPins(int channel){
  switch (channel){
    case 1:
    digitalWrite(curChannel.ch2Pin,LOW);
    digitalWrite(curChannel.ch3Pin,LOW);
    break;
    case 2:
    digitalWrite(curChannel.ch2Pin,HIGH);
    digitalWrite(curChannel.ch3Pin,LOW);
    break;
    case 3:
    digitalWrite(curChannel.ch2Pin,LOW);
    digitalWrite(curChannel.ch3Pin,HIGH);
    break;
  }
}

void moveSlidePot(int pot, double target){

}
