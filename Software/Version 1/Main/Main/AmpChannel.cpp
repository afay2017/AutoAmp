  #include <Arduino.h>
class AmpChannel
{
private:
  int channel;
  int head;
  bool lead;
  bool mesaEffects;
  bool headEffects;
  int bypassPin = 1;
  int headPin = 1;
  int mesaEffectsPin = 1;
  int headEffectsPin = 1;
  int leadPin = 1;
  int ch2Pin = 1;
  int ch3Pin = 1;
  int soloPin = 1;
public:
  AmpChannel(int channelNumber);
  void setAmpChannel(int channel);
  void setHead(int head);
  int getHead();
  void setLead(bool on);
  bool getLead();
  void setMesaEffects(bool on);
  void setHeadEffects(bool on);
  bool getMesaEffects();
  bool getHeadEffects();
  const static int ORANGE;
  const static int CRUNCH;
  const static int LEAD;

};

const int AmpChannel::ORANGE = 0;
const int AmpChannel::CRUNCH = 1;
const int AmpChannel::LEAD   = 2;

AmpChannel::AmpChannel(int channelNumber)
{
 this->channel = channelNumber;
 pinMode(bypassPin,OUTPUT);
 pinMode(headPin,OUTPUT);
 pinMode(mesaEffectsPin,OUTPUT);
 pinMode(headEffectsPin,OUTPUT);
 pinMode(leadPin,OUTPUT);
 pinMode(ch2Pin,OUTPUT);
 pinMode(ch3Pin,OUTPUT);
 pinMode(soloPin,OUTPUT);

}

void AmpChannel::setAmpChannel(int channelNumber)
{
 this->channel = channelNumber;
}

void AmpChannel::setMesaEffects(bool on)
{
 this->mesaEffects = on;
}

bool AmpChannel::getMesaEffects()
{
 return (bool)mesaEffects;
}

void AmpChannel::setHeadEffects(bool on)
{
 this->headEffects = on;
}

bool AmpChannel::getHeadEffects()
{
 return (bool)headEffects;
}

void AmpChannel::setHead(int head)
{
 this->head = head;
 switch (head){
   case ORANGE:
   digitalWrite(headPin, LOW);
   break;

   case CRUNCH:
   digitalWrite(headPin, HIGH);
   digitalWrite(leadPin, LOW);
   break;

   case LEAD:
   digitalWrite(headPin, HIGH);
   digitalWrite(leadPin, HIGH);
   break;

 }
}

int AmpChannel::getHead()
{
 return (bool)head;
}
