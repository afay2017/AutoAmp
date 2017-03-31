    #include <Arduino.h>
    #include <AmpChannel.cpp>
    #include <Servo.h>
    #include <elapsedMillis.h>

    elapsedMillis timer0;

    #define interval 750
    // the interval in mS

 AmpChannel curChannel;
 AmpChannel channel1;
 AmpChannel channel2;

 Servo gainServoORANGE;
 Servo volServoORANGE;
 Servo toneServoORANGE;

 Servo gainServoPIHRANA;
 Servo volServoPIHRANA;
 Servo toneServoPIHRANA;


 int slidePotOffset;
 bool moving;
 int ch12SwitchPin;
 int ch23SwitchPin;
 int bypassSwitchPin;

 int ampSwitchState;
 int mesaEffectsSwitchState;
 int headEffectsSwitchState;

void setup() {
  // put your setup code here, to run once:
  curChannel = new AmpChannel((int)1);

  channel1 = new AmpChannel(1);
  channel2 = new AmpChannel(2);
  channel3 = new AmpChannel(3);

  channel1.setHead(curChannel.ORANGE);
  channel2.setHead(curChannel.CRUNCH);

  channel1.setMesaEffects(false);
  channel2.setMesaEffects(false);

  channel1.setHeadEffects(true);
  channel2.setHeadEffects(true);

  channel1.setGain(5);
  channel2.setGain(100);

  AmpChannel channels [] = {channel1,channel2,channel3};


  for (int i = 0; i < 55; i++) {
    pinMode(i,INPUT);
  }


  Serial.begin(9600);

  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);

  pinMode(curChannel.headPin,OUTPUT);
  pinMode(curChannel.bypassPin,OUTPUT);
  pinMode(curChannel.headEffectsPin,OUTPUT);
  pinMode(curChannel.mesaEffectsPin,OUTPUT);

  pinMode(curChannel.gainPotPin,INPUT);

  pinMode(curChannel.gainMotorLPin,OUTPUT);
  pinMode(curChannel.gainMotorRPin,OUTPUT);

  pinMode(curChannel.ampSwitchPin,INPUT);
  pinMode(curChannel.mesaEffectsPin,INPUT);
  pinMode(curChannel.mesaEffectsPin,INPUT);


  gainServoORANGE.attach(curChannel.gainServoPinORANGE);
  volServoORANGE.attach(curChannel.volServoPinORANGE);
  toneServoORANGE.attach(curChannel.toneServoPinORANGE);

  gainServoPIHRANA.attach(curChannel.gainServoPinPIHRANA);
  volServoPIHRANA.attach(curChannel.volServoPinPIHRANA);
  toneServoPIHRANA.attach(curChannel.toneServoPinPIHRANA);

  timer0 = 0;

  slidePotOffset = 1;
  //Serial.println("OFF");
}

void loop() {

if(digitalRead(8) == 1){
  setChannel(1);
} else {
  setChannel(2);
}



freezeSlidePots();

  if (moving){
    moveSlidePots();
  } else {
    freezeSlidePots();
    curChannel.setGain(analogRead(curChannel.gainPotPin)/5.68 );
    curChannel.setVolume(analogRead(curChannel.volPotPin)/5.68 );
    curChannel.setTone(analogRead(curChannel.tonePotPin)/5.68 );
  }

  if(timer0 > interval){
    timer0 = 0;
    moving = false;
  }


  //Serial.println(digitalRead(8));
  //Serial.println(analogRead(curChannel.gainPotPin)/5.68);
  applyServo();
}

void applyPins(){
  //digitalWrite(curChannel.bypassPin,curChannel.getBypassInt());
  //Serial.println(curChannel.getHead());
  switch (curChannel.getHead()){
    case curChannel.ORANGE:
    digitalWrite(curChannel.headPin, LOW);
    //Serial.println("ORANGE");
    break;

    case curChannel.CRUNCH:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, LOW);
    //Serial.println("CRUNCH");
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

void applyServo(){

  gainServoORANGE.write(curChannel.getGain());
  volServoORANGE.write(curChannel.getVolume());
  toneServoORANGE.write(curChannel.getTone());

  gainServoPIHRANA.write(curChannel.getGain());
  volServoPIHRANA.write(curChannel.getVolume());
  toneServoPIHRANA.write(curChannel.getTone());
  //Serial.println(curChannel.getGain());

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

void moveSlidePots(){
  if (analogRead(curChannel.gainPotPin)/5.68 > curChannel.getGain() + slidePotOffset){
    //Serial.println("L");
    digitalWrite(curChannel.gainMotorLPin,1);
    digitalWrite(curChannel.gainMotorRPin,0);
  } else if (analogRead(curChannel.gainPotPin)/5.68 < curChannel.getGain() - slidePotOffset){
    digitalWrite(curChannel.gainMotorLPin,0);
    digitalWrite(curChannel.gainMotorRPin,1);
    //Serial.println("R");
  } else {
    digitalWrite(curChannel.gainMotorLPin,0);
    digitalWrite(curChannel.gainMotorRPin,0);
    //Serial.println("N");
  }

  if (analogRead(curChannel.tonePotPin)/5.68 > curChannel.getTone() + slidePotOffset){
    //Serial.println("L");
    digitalWrite(curChannel.toneMotorLPin,1);
    digitalWrite(curChannel.toneMotorRPin,0);
  } else if (analogRead(curChannel.tonePotPin)/5.68 < curChannel.getTone() - slidePotOffset){
    digitalWrite(curChannel.toneMotorLPin,0);
    digitalWrite(curChannel.toneMotorRPin,1);
    //Serial.println("R");
  } else {
    digitalWrite(curChannel.toneMotorLPin,0);
    digitalWrite(curChannel.toneMotorRPin,0);
    //Serial.println("N");
  }

  if (analogRead(curChannel.volPotPin)/5.68 > curChannel.getVolume() + slidePotOffset){
    //Serial.println("L");
    digitalWrite(curChannel.volMotorLPin,1);
    digitalWrite(curChannel.volMotorRPin,0);
  } else if (analogRead(curChannel.volPotPin)/5.68 < curChannel.getVolume() - slidePotOffset){
    digitalWrite(curChannel.volMotorLPin,0);
    digitalWrite(curChannel.volMotorRPin,1);
    //Serial.println("R");
  } else {
    digitalWrite(curChannel.volMotorLPin,0);
    digitalWrite(curChannel.volMotorRPin,0);
    //Serial.println("N");
  }
}
void freezeSlidePots(){
    digitalWrite(curChannel.gainMotorLPin,0);
    digitalWrite(curChannel.gainMotorRPin,0);
    digitalWrite(curChannel.toneMotorLPin,0);
    digitalWrite(curChannel.toneMotorRPin,0);
    digitalWrite(curChannel.volMotorLPin,0);
    digitalWrite(curChannel.volMotorRPin,0);
}

void setChannel(int channel){
  Serial.println(channel);
  switch (channel){
  case 1:
    if (curChannel.getAmpChannelNumber() != channel[0].getAmpChannelNumber()){
      channel[curChannel.getAmpChannelNumber()-1] = curChannel;
      timer0 = 0;
      moving = true;
    }
    curChannel = channel[0];
    applyPins();
    break;
  case 2:
    if (curChannel.getAmpChannelNumber() != channel[1].getAmpChannelNumber()){
      channel[curChannel.getAmpChannelNumber()-1] = curChannel;
      timer0 = 0;
      moving = true;
    }
    curChannel = channel[1];
    applyPins();
    break;
  case 3:
    if (curChannel.getAmpChannelNumber() != channel[2].getAmpChannelNumber()){
      channel[curChannel.getAmpChannelNumber()-1] = curChannel;
      timer0 = 0;
      moving = true;
    }
    curChannel = channel[2];
    applyPins();
    break;
  }
}

  void checkSwitches(){
    if(digitalRead(curChannel.ampSwitchPin)==1 && ampSwitchState != 1){
        ampSwitchState = 1;
        curChannel.incHead();
    } else if(digitalRead(curChannel.ampSwitchPin) == 0){
      ampSwitchState = 0;
    }

    if(digitalRead(curChannel.headEffectsSwitchPin)==1 && headEffectsSwitchState != 1){
        ampSwitchState = 1;
        curChannel.incHead();
    } else if(digitalRead(curChannel.headEffectsSwitchPin) == 0){
      ampSwitchState = 0;
    }

    if(digitalRead(curChannel.mesaEffectsSwitchPin)==1 && mesaEffectsSwitchState != 1){
        ampSwitchState = 1;
        curChannel.incHead();
    } else if(digitalRead(curChannel.mesaEffectsSwitchPin) == 0){
      ampSwitchState = 0;
    }
  }
