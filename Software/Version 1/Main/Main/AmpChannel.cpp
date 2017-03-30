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
  AmpChannel()
  {
   this->channel = 1;
  }
  AmpChannel(int channelNumber)
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
  void setAmpChannelNumber(int channelNumber)
  {
    if (channelNumber > 3){
      channelNumber = 3;
    } else if( channelNumber < 1){
      channelNumber = 1;
    }
   this->channel = channelNumber;
  }

  int getAmpChannelNumber()
  {
   return (int)channel;
  }

  void setMesaEffects(bool on)
  {
   this->mesaEffects = on;
  }

  bool getMesaEffects()
  {
   return (bool)mesaEffects;
  }

  void setHeadEffects(bool on)
  {
   this->headEffects = on;
  }

  bool getHeadEffects()
  {
   return (bool)headEffects;
  }

  void setBypass(bool on)
  {
   this->bypass = on;
  }

  bool getBypass()
  {
   return (bool)bypass;
  }

  int getBypassInt()
  {
   return (int)bypass;
  }

  void incHead(){
    setHead(head+1);
  }

  void setHead(int head)
  {
    if (head > 3){
      head = 1;
    }
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

  int getHead()
  {
   return (int)head;
  }

  void setGain(double value){
    gain = value;
  }

  double getGain(){
    return gain;
  }

  void setBlend(double value){
    blend = value;
  }

  double getBlend(){
    return blend;
  }

  void setTone(double value){
    tone = value;
  }

  double getTone(){
    return tone;
  }

  void setVolume(double value){
    volume = value;
  }

  double getVolume(){
    return volume;
  }
  const static int ORANGE = 1;
  const static int CRUNCH = 2;
  const static int LEAD   = 3;

  void snapToSaved(); //Must be refreshed constnatly
  void setPointReached();

  int bypassPin = 17;
  int headPin = 16;
  int mesaEffectsPin = 15;
  int headEffectsPin = 14;
  int leadPin = 1;
  int ch2Pin = 1;
  int ch3Pin = 1;
  int soloPin = 1;

  int gainServoPinORANGE = 2;
  int volServoPinORANGE = 3;
  int toneServoPinORANGE = 4;

  int gainServoPinPIHRANA = 5;
  int volServoPinPIHRANA = 6;
  int toneServoPinPIHRANA = 7;

  int gainPotPin = A4;
  int volPotPin = A5;
  int tonePotPin = A6;
  int blendPotPin = A7;

  int gainMotorLPin = 27;
  int gainMotorRPin = 26;

  int volMotorLPin = 1;
  int volMotorRPin = 1;

  int toneMotorLPin = 1;
  int toneMotorRPin = 1;

  int blendMotorLPin = 1;3
  int blendMotorRPin = 1;

  int ampSwitchPin = -1;
  int mesaEffectsSwitchPin = -1;
  int headEffectsSwitchPin = -1;

};

// const int AmpChannel::ORANGE = 0;
// const int AmpChannel::CRUNCH = 1;
// const int AmpChannel::LEAD   = 2;
