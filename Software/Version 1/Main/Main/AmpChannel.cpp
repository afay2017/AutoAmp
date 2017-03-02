  #include <Arduino.h>
class AmpChannel
{
private:
  int channel;
  int head;
  bool lead;
  bool mesaEffects;
  bool headEffects;
  bool bypass;

  double gain;
  double blend;
  double tone;
  double volume;

public:
  AmpChannel();
  AmpChannel(int channelNumber);
  void setAmpChannelNumber(int channel);
  int getAmpChannelNumber();
  void setHead(int head);
  int getHead();
  void setLead(bool on);
  bool getLead();
  void setMesaEffects(bool on);
  bool getMesaEffects();
  void setHeadEffects(bool on);
  bool getHeadEffects();
  void setBypass(bool on);
  bool getBypass();
  int getBypassInt();
  const static int ORANGE = 1;
  const static int CRUNCH = 2;
  const static int LEAD   = 3;

  void setGain(double value);
  void setBlend(double value);
  void setTone(double value);
  void setVolume(double value);

  double getGain();
  double getBlend();
  double getTone();
  double getVolume();

  void snapToSaved(); //Must be refreshed constnatly
  void setPointReached();

  int bypassPin = 1;
  int headPin = 1;
  int mesaEffectsPin = 1;
  int headEffectsPin = 1;
  int leadPin = 1;
  int ch2Pin = 1;
  int ch3Pin = 1;
  int soloPin = 1;

};

// const int AmpChannel::ORANGE = 0;
// const int AmpChannel::CRUNCH = 1;
// const int AmpChannel::LEAD   = 2;

AmpChannel::AmpChannel(int channelNumber)
{
 this->channel = channelNumber;
 // pinMode(bypassPin,OUTPUT);
 // pinMode(headPin,OUTPUT);
 // pinMode(mesaEffectsPin,OUTPUT);
 // pinMode(headEffectsPin,OUTPUT);
 // pinMode(leadPin,OUTPUT);
 // pinMode(ch2Pin,OUTPUT);
 // pinMode(ch3Pin,OUTPUT);
 // pinMode(soloPin,OUTPUT);

}
AmpChannel::AmpChannel()
{
 this->channel = 1;
}

void AmpChannel::setAmpChannelNumber(int channelNumber)
{
  if (channelNumber > 3){
    channelNumber = 3;
  } else if( channelNumber < 1){
    channelNumber = 1;
  }
 this->channel = channelNumber;
}

int AmpChannel::getAmpChannelNumber()
{
 return (int)channel;
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

void AmpChannel::setBypass(bool on)
{
 this->bypass = on;
}

bool AmpChannel::getBypass()
{
 return (bool)bypass;
}

int AmpChannel::getBypassInt()
{
 return (int)bypass;
}

void AmpChannel::setHead(int head)
{
 this->head = head;
 // switch (head){
 //   case ORANGE:
 //   digitalWrite(headPin, LOW);
 //   break;
 //
 //   case CRUNCH:
 //   digitalWrite(headPin, HIGH);
 //   digitalWrite(leadPin, LOW);
 //   break;
 //
 //   case LEAD:
 //   digitalWrite(headPin, HIGH);
 //   digitalWrite(leadPin, HIGH);
 //   break;
 // }
}

int AmpChannel::getHead()
{
 return (bool)head;
}

void AmpChannel::setGain(double value){
  gain = value;
}

double AmpChannel::getGain(){
  return gain;
}

void AmpChannel::setBlend(double value){
  blend = value;
}

double AmpChannel::getBlend(){
  return blend;
}

void AmpChannel::setTone(double value){
  tone = value;
}

double AmpChannel::getTone(){
  return tone;
}

void AmpChannel::setVolume(double value){
  volume = value;
}

double AmpChannel::getVolume(){
  return volume;
}
