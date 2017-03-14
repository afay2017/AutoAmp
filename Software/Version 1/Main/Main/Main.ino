    #include <Arduino.h>
    #include <AmpChannel.cpp>

 AmpChannel curChannel;
 AmpChannel channel1;
 AmpChannel channel2;

void setup() {
  // put your setup code here, to run once:
  curChannel = new AmpChannel((int)1);
  channel1 = new AmpChannel(1);
  channel1 = new AmpChannel(2);

  channel1.setHead(curChannel.ORANGE);
  channel2.setHead(curChannel.ORANGE);

  channel1.setMesaEffects(false);
  channel2.setMesaEffects(false);

  channel1.setHeadEffects(true);
  channel2.setHeadEffects(true);



  Serial.begin(9600);

  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);

  pinMode(curChannel.headPin,OUTPUT);
  pinMode(curChannel.bypassPin,OUTPUT);
  pinMode(curChannel.headEffectsPin,OUTPUT);
  pinMode(curChannel.mesaEffectsPin,OUTPUT);


  //Serial.println("OFF");
}

void loop() {
  if (digitalRead(8)==HIGH){
    //digitalWrite(curChannel.bypassPin, LOW);
    curChannel = channel1;
    applyPins();
    //Serial.println("OFF");
  } else {
    curChannel = channel2;
    applyPins();
    //Serial.println("ON");
    //digitalWrite(curChannel.bypassPin, HIGH);
  }
}

void applyPins(){
  //digitalWrite(curChannel.bypassPin,curChannel.getBypassInt());
  Serial.println(curChannel.getHead());
  switch (curChannel.getHead()){
    case curChannel.ORANGE:
    digitalWrite(curChannel.headPin, LOW);
    Serial.println("ORANGE");
    break;

    case curChannel.CRUNCH:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, LOW);
    Serial.println("CRUNCH");
    break;

    case curChannel.LEAD:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, HIGH);
    break;
  }

  digitalWrite(curChannel.headEffectsPin,curChannel.getHeadEffects());
  digitalWrite(curChannel.mesaEffectsPin,curChannel.getMesaEffects());

//  applyMesaChannelPins(curChannel.getAmpChannelNumber());

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
