    #include <Arduino.h>
    #include <AmpChannel.cpp>

AmpChannel curChannel;

void setup() {
  // put your setup code here, to run once:
  AmpChannel channel1 = new AmpChannel(1);

  pinMode(1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void applyPins(){
  digitalWrite(curChannel.bypassPin,){

  }
}
}
