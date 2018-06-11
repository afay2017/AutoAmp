    #include <Arduino.h>
    #include <AmpChannel.cpp>
    #include <Servo.h>
    #include <elapsedMillis.h>
    #include <EEPROM.h>

    elapsedMillis timer0;

    #define interval 750
    // the interval in mS

 AmpChannel curChannel;
 AmpChannel channel1;
 AmpChannel channel2;
 AmpChannel channel3;
// int numOfChannels = 3;
 AmpChannel channels[3];

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

 int saveState;
 int ampSwitchState;
 int cycleChannelSwitchState;
 int mesaEffectsSwitchState;
 int headEffectsSwitchState;

struct savedSettings {
  int channelnum;
  int mesachannel;
  int gain;
  int vol;
  int blend;
  int tone;
  bool mesaEffects;
  bool headEffects;
  int head;
};

void writeToEEPROM(){
  int eeAddress = 0;
  savedSettings settings[3];
  for (int i = 0; i < 3; i++){
    settings[i].channelnum  = channels[i].getAmpChannelNumber();
    settings[i].mesachannel = channels[i].getAmpChannelNumber();
    settings[i].gain        = channels[i].getGain();
    settings[i].tone        = channels[i].getTone();
    settings[i].vol         = channels[i].getVolume();
    settings[i].blend       = channels[i].getBlend();
    settings[i].mesaEffects = channels[i].getMesaEffects();
    settings[i].headEffects = channels[i].getHeadEffects();
    settings[i].head        = channels[i].getHead();
  }
  Serial.println(channels[1].getGain());
  Serial.println(settings[1].gain);
  for (int i = 0; i < 3; i++){
      //Serial.println(channels[i].getGain());
      //Serial.println(settings[i].gain);
      EEPROM.put(eeAddress,settings[i]);
      eeAddress += sizeof(savedSettings);
    }
}

void readFromEEPROM(){
  int eeAddress = 0;
  savedSettings settings[3];
  for (int i = 0; i < 3; i++){
    EEPROM.get(eeAddress,settings[i]);
    eeAddress += sizeof(savedSettings);
  }
  for (int i = 0; i < 3; i++){
    //Serial.println(settings[i].gain);
    // channels[i].setAmpChannelNumber(settings[i].channelnum);
    // channels[i].setGain(settings[i].gain);
    // channels[i].setTone(settings[i].tone);
    // channels[i].setVolume(settings[i].vol);
    // channels[i].setBlend(settings[i].blend);
    // channels[i].setMesaEffects(settings[i].mesaEffects);
    // channels[i].setHeadEffects(settings[i].headEffects);
    // channels[i].setHead(settings[i].head);
  }
}

void applyFootSwitchLED(int channel){
  switch (channel) {
    case 1:
      digitalWrite(curChannel.footCh1LED,HIGH);
      break;
    case 2:
      digitalWrite(curChannel.footCh1LED,LOW);
      digitalWrite(curChannel.footCh2orCh3LED,LOW);
      break;
    case 3:
        digitalWrite(curChannel.footCh1LED,LOW);
        digitalWrite(curChannel.footCh2orCh3LED,HIGH);
        break;
      }
}

void applyPins(){
  //digitalWrite(curChannel.bypassPin,curChannel.getBypassInt());
  //Serial.println(curChannel.getHead());
  switch (curChannel.getHead()){
    case curChannel.ORANGE:
    digitalWrite(curChannel.headPin, LOW);
    //Serial.println("ORANGE");
    digitalWrite(curChannel.headLEDPin, HIGH);
    break;

    case curChannel.CRUNCH:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, LOW);
    //Serial.println("CRUNCH");
    digitalWrite(curChannel.headLEDPin, LOW);
    break;

    case curChannel.LEAD:
    digitalWrite(curChannel.headPin, HIGH);
    digitalWrite(curChannel.leadPin, HIGH);
    digitalWrite(curChannel.headLEDPin, LOW);
    break;
  }

  digitalWrite(curChannel.headEffectsPin,curChannel.getMesaEffects());
  digitalWrite(curChannel.mesaEffectsPin,curChannel.getMesaEffects());
  digitalWrite(curChannel.headEffectsLEDPin,curChannel.getHeadEffects());
  digitalWrite(curChannel.mesaEffectsLEDPin,curChannel.getMesaEffects());


  applyMesaChannelPins(curChannel.getAmpChannelNumber());
  applyFootSwitchLED(curChannel.getAmpChannelNumber());



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

void applyMesaSolo(bool solo){
  if(solo){
    digitalWrite(curChannel.soloPin,HIGH);
  } else {
    digitalWrite(curChannel.soloPin,LOW);
  }
}

void moveSlidePots(){
  if (analogRead(curChannel.gainPotPin)/5.68 > curChannel.getGain() + slidePotOffset){
    Serial.println("L");
    digitalWrite(curChannel.gainMotorLPin,1);
    digitalWrite(curChannel.gainMotorRPin,0);
  } else if (analogRead(curChannel.gainPotPin)/5.68 < curChannel.getGain() - slidePotOffset){

    digitalWrite(curChannel.gainMotorLPin,0);
    digitalWrite(curChannel.gainMotorRPin,1);
    Serial.println("R");
  } else {
    digitalWrite(curChannel.gainMotorLPin,0);
    digitalWrite(curChannel.gainMotorRPin,0);
    Serial.println("N");
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

  if (analogRead(curChannel.blendPotPin)/5.68 > curChannel.getBlend() + slidePotOffset){
    //Serial.println("L");
    digitalWrite(curChannel.blendMotorLPin,1);
    digitalWrite(curChannel.blendMotorRPin,0);
  } else if (analogRead(curChannel.blendPotPin)/5.68 < curChannel.getBlend() - slidePotOffset){
    digitalWrite(curChannel.blendMotorLPin,0);
    digitalWrite(curChannel.blendMotorRPin,1);
    //Serial.println("R");
  } else {
    digitalWrite(curChannel.blendMotorLPin,0);
    digitalWrite(curChannel.blendMotorRPin,0);
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
    digitalWrite(curChannel.blendMotorLPin,0);
    digitalWrite(curChannel.blendMotorRPin,0);
}

void setChannel(int channel){
  //Serial.println(channel);
  //switch (channel){
  //case 1:
  if (channel < 0 || channel > 3){
    channel = 1;
  }
  if (curChannel.getAmpChannelNumber() != channels[channel-1].getAmpChannelNumber()){
    curChannel.setGain(analogRead(curChannel.gainPotPin)/5.68 );
    curChannel.setVolume(analogRead(curChannel.volPotPin)/5.68 );
    curChannel.setTone(analogRead(curChannel.tonePotPin)/5.68 );
    channels[curChannel.getAmpChannelNumber()-1] = curChannel;
    timer0 = 0;
    moving = true;
  }
  curChannel = channels[channel-1];
  applyPins();

  // case 2:
  //   if (curChannel.getAmpChannelNumber() != channels[1].getAmpChannelNumber()){
  //     curChannel.setGain(analogRead(curChannel.gainPotPin)/5.68 );
  //     curChannel.setVolume(analogRead(curChannel.volPotPin)/5.68 );
  //     curChannel.setTone(analogRead(curChannel.tonePotPin)/5.68 );
  //     channels[curChannel.getAmpChannelNumber()-1] = curChannel;
  //     timer0 = 0;
  //     moving = true;
  //   }
  //   curChannel = channels[1];
  //   applyPins();
  //   break;
  // case 3:
  //   if (curChannel.getAmpChannelNumber() != channels[2].getAmpChannelNumber()){
  //     curChannel.setGain(analogRead(curChannel.gainPotPin)/5.68 );
  //     curChannel.setVolume(analogRead(curChannel.volPotPin)/5.68 );
  //     curChannel.setTone(analogRead(curChannel.tonePotPin)/5.68 );
  //     channels[curChannel.getAmpChannelNumber()-1] = curChannel;
  //     timer0 = 0;
  //     moving = true;
  //   }
  //   curChannel = channels[2];
  //   applyPins();
  //   break;
  //}
}

  void checkSwitches(){
    //FootSwitch
    if (digitalRead(curChannel.foot1and2Pin)==1 && digitalRead(curChannel.foot2and3Pin)==0){
      setChannel(1);
    } else if (digitalRead(curChannel.foot1and2Pin)==1 && digitalRead(curChannel.foot2and3Pin)==1){
      setChannel(2);
    } else if (digitalRead(curChannel.foot1and2Pin)==0 && digitalRead(curChannel.foot2and3Pin)==1){
      setChannel(3);
    }

    if (digitalRead(curChannel.mesaEffectsSwitchPin)==1 && digitalRead(curChannel.headEffectsSwitchPin)==1 && saveState != 1){
      writeToEEPROM();
    } else if(digitalRead(curChannel.mesaEffectsSwitchPin)==0 || digitalRead(curChannel.headEffectsSwitchPin)==0){
      saveState = 0;
    }

    if(digitalRead(curChannel.ampSwitchPin)==1 && ampSwitchState != 1){
        ampSwitchState = 1;
        curChannel.incHead();
        applyPins();
    } else if(digitalRead(curChannel.ampSwitchPin) == 0){
      ampSwitchState = 0;
    }

    if(digitalRead(curChannel.cycleChannelSwitchPin)==1 && cycleChannelSwitchState != 1){
        cycleChannelSwitchState = 1;
        setChannel(curChannel.getAmpChannelNumber()+1);
        applyPins();
    } else if(digitalRead(curChannel.cycleChannelSwitchPin) == 0){
      cycleChannelSwitchState = 0;
    }

    if(digitalRead(curChannel.headEffectsSwitchPin)==1 && headEffectsSwitchState != 1){
        headEffectsSwitchState = 1;
        curChannel.toggleHeadEffects();
        applyPins();
    } else if(digitalRead(curChannel.headEffectsSwitchPin) == 0){
      headEffectsSwitchState = 0;
    }

    if(digitalRead(curChannel.mesaEffectsSwitchPin)==1 && mesaEffectsSwitchState != 1){
        mesaEffectsSwitchState = 1;
        curChannel.toggleMesaEffects();
        applyPins();
    } else if(digitalRead(curChannel.mesaEffectsSwitchPin) == 0){
      mesaEffectsSwitchState = 0;
    }

    digitalWrite(curChannel.bypassPin,digitalRead(curChannel.footAmpPin));
    Serial.println(digitalRead(curChannel.footAmpPin));

  }

  void setup() {

     ampSwitchState = 0;
     cycleChannelSwitchState = 0;
     mesaEffectsSwitchState = 0;
     headEffectsSwitchState = 0;

     channel1.setAmpChannelNumber(1);
     channel2.setAmpChannelNumber(2);
     channel3.setAmpChannelNumber(3);

    channel1.setHead(curChannel.ORANGE);
    channel2.setHead(curChannel.CRUNCH);

    channel1.setMesaEffects(false);
    channel2.setMesaEffects(false);

    channel1.setHeadEffects(true);
    channel2.setHeadEffects(true);

    channel1.setGain(5);
    channel2.setGain(100);

     channels[0] = channel1;
     channels[1] = channel2;
     channels[2] = channel3;


    for (int i = 0; i < 55; i++) {
      pinMode(i,INPUT);
    }


     Serial.begin(9600);


    pinMode(8,INPUT_PULLUP);
    pinMode(9,INPUT_PULLUP);

    pinMode(curChannel.footAmpPin,INPUT);
    pinMode(curChannel.footSoloPin, INPUT);
    pinMode(curChannel.footFXPin, INPUT);
    pinMode(curChannel.foot2and3Pin, INPUT);
    pinMode(curChannel.foot1and2Pin, INPUT);

    pinMode(curChannel.footCh1LED, OUTPUT);
    pinMode(curChannel.footCh2orCh3LED, OUTPUT);

    pinMode(curChannel.headPin,OUTPUT);
    pinMode(curChannel.bypassPin,OUTPUT);
    pinMode(curChannel.headEffectsPin,OUTPUT);
    pinMode(curChannel.mesaEffectsPin,OUTPUT);

    pinMode(curChannel.gainPotPin,INPUT);

    pinMode(curChannel.gainMotorLPin,OUTPUT);
    pinMode(curChannel.gainMotorRPin,OUTPUT);

    pinMode(curChannel.toneMotorLPin,OUTPUT);
    pinMode(curChannel.toneMotorRPin,OUTPUT);

    pinMode(curChannel.volMotorLPin,OUTPUT);
    pinMode(curChannel.volMotorRPin,OUTPUT);

    pinMode(curChannel.blendMotorLPin,OUTPUT);
    pinMode(curChannel.blendMotorRPin,OUTPUT);

    pinMode(curChannel.ampSwitchPin,INPUT);
    pinMode(curChannel.headEffectsSwitchPin,INPUT);
    pinMode(curChannel.mesaEffectsSwitchPin,INPUT);
    pinMode(curChannel.cycleChannelSwitchPin, INPUT);

    pinMode(curChannel.headLEDPin,OUTPUT);
    pinMode(curChannel.headEffectsLEDPin,OUTPUT);
    pinMode(curChannel.mesaEffectsLEDPin,OUTPUT);
    pinMode(curChannel.bypassLEDPin, OUTPUT);


    gainServoORANGE.attach(curChannel.gainServoPinORANGE);
    volServoORANGE.attach(curChannel.volServoPinORANGE);
    toneServoORANGE.attach(curChannel.toneServoPinORANGE);

    gainServoPIHRANA.attach(curChannel.gainServoPinPIHRANA);
    volServoPIHRANA.attach(curChannel.volServoPinPIHRANA);
    toneServoPIHRANA.attach(curChannel.toneServoPinPIHRANA);

    timer0 = 0;

    slidePotOffset = 50;


    readFromEEPROM();
  }

   void loop() {

     // if(digitalRead(9) == 1){
     //   setChannel(1);
     // } else {
     //   setChannel(2);
     // }




  // channels[0].setGain(20);
  // channels[0].setVolume(20);
  // channels[0].setTone(20);
  // channels[0].setBlend(20);
  //
  // channels[1].setGain(120);
  // channels[1].setVolume(120);
  // channels[1].setTone(120);
  // channels[1].setBlend(120);
  //
  // channels[2].setGain(20);
  // channels[2].setVolume(20);
  // channels[2].setTone(20);
  // channels[2].setBlend(20);

    if (moving){
      moveSlidePots();
    } else {
      freezeSlidePots();
      curChannel.setGain(analogRead(curChannel.gainPotPin)/5.68 );
      curChannel.setVolume(analogRead(curChannel.volPotPin)/5.68 );
      curChannel.setTone(analogRead(curChannel.tonePotPin)/5.68 );
      curChannel.setBlend(analogRead(curChannel.tonePotPin)/5.68 );
    }



    Serial.print("Gain: ");
    Serial.print(analogRead(curChannel.gainPotPin)/5.68);
    Serial.print(" Tone: ");
    Serial.print(analogRead(curChannel.tonePotPin)/5.68);
    Serial.print(" Vol: ");
    Serial.println(analogRead(curChannel.volPotPin)/5.68);
    // Serial.print(" Blend: ");


    //Serial.print("Gain: ");
  //  Serial.print(curChannel.getHeadEffects());


    // Serial.println(analogRead(curChannel.blendPotPin)/5.68);
    //Serial.print(curChannel.getAmpChannelNumber());
    //Serial.print(digitalRead(curChannel.cycleChannelSwitchPin));
    if(timer0 > interval){
      timer0 = 0;
      moving = false;
    }


     // Serial.print(digitalRead(curChannel.footAmpPin));
     // Serial.print(digitalRead(curChannel.footSoloPin));
     // Serial.print(digitalRead(curChannel.footFXPin));
     // Serial.print(digitalRead(curChannel.foot2and3Pin));
     // Serial.println(digitalRead(curChannel.foot1and2Pin));
     // Serial.print(digitalRead(curChannel.mesaEffectsSwitchPin));
     // Serial.println(digitalRead(curChannel.cycleChannelSwitchPin));
     // Serial.println(analogRead(curChannel.gainPotPin)/5.68);
    applyServo();
    checkSwitches();
   }
