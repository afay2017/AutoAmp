  #include <Arduino.h>
class AmpChannel
{
private:

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
  int channel;
  AmpChannel();
  AmpChannel(int channelNumber);
  void setAmpChannelNumber(int channelNumber);
  int getAmpChannelNumber();
  void setMesaEffects(bool on);
  bool getMesaEffects();
  void setHeadEffects(bool on);
  bool getHeadEffects();
  void setBypass(bool on);
  bool getBypass();
  int getBypassInt();
  void incHead();
  void setHead(int head);
  int getHead();
  void setGain(double value);
  double getGain();
  void setBlend(double value);
  double getBlend();
  void setTone(double value);
  double getTone();
  void setVolume(double value);
  double getVolume();


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
    // pinMoSde(ch2Pin,OUTPUT);
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

  int bypassPin = 25;
  int headPin = 24;
  int mesaEffectsPin = 23;
  int headEffectsPin = 22;
  int leadPin = 51;
  int ch2Pin = 52;
  int ch3Pin = 53;
  int soloPin = 50;

  int gainServoPinORANGE = 4;
  int volServoPinORANGE = 2;
  int toneServoPinORANGE = 3;

  int gainServoPinPIHRANA = 7;
  int volServoPinPIHRANA = 5;
  int toneServoPinPIHRANA = 6;

  int gainPotPin = A1;
  int volPotPin = A2;
  int tonePotPin = A3;
  int blendPotPin = A4;

  int gainMotorLPin = 45;
  int gainMotorRPin = 44;

  int volMotorLPin = 43;
  int volMotorRPin = 42;

  int toneMotorLPin = 41;
  int toneMotorRPin = 40;

  int blendMotorLPin = 39;
  int blendMotorRPin = 38;

  int ampSwitchPin = -1;
  int mesaEffectsSwitchPin = -1;
  int headEffectsSwitchPin = -1;

};

// const int AmpChannel::ORANGE = 0;
// const int AmpChannel::CRUNCH = 1;
// const int AmpChannel::LEAD   = 2;
