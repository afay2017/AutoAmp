  #include <Arduino.h>
class AmpChannel
{
private:
  int channelnum;
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
    channelnum = 1;
  }
  // AmpChannel(int channelNumber)
  // {
  //   channelnum = channelNumber;
  //   // pinMode(bypassPin,OUTPUT);
  //   // pinMode(headPin,OUTPUT);
  //   // pinMode(mesaEffectsPin,OUTPUT);
  //   // pinMode(headEffectsPin,OUTPUT);
  //   // pinMode(leadPin,OUTPUT);
  //   // pinMode(ch2Pin,OUTPUT);
  //   // pinMode(ch3Pin,OUTPUT);
  //   // pinMode(soloPin,OUTPUT);
  //   setAmpChannelNumber(channelNumber);
  // }

  // byte[] toByteArray(){
  //   byte[] = new
  // }

  void setAmpChannelNumber(int channelNumber)
  {
    if (channelNumber > 3){
      channelNumber = 3;
    } else if( channelNumber < 1){
      channelNumber = 1;
    }
   channelnum = channelNumber;
  }

  int getAmpChannelNumber()
  {
   return channelnum;
  }

  void setMesaEffects(bool on)
  {
   this->mesaEffects = on;
  }

  void toggleMesaEffects()
  {
    this->mesaEffects = !this->mesaEffects;
  }

  bool getMesaEffects()
  {
   return (bool)mesaEffects;
  }

  void setHeadEffects(bool on)
  {
   this->headEffects = on;
  }

  void toggleHeadEffects()
  {
    this->headEffects = !this->headEffects;
  }

  bool getHeadEffects()
  {
   return (bool)headEffects;
  }

  void setBypass(bool on)
  {
   this->bypass = on;
  }

  void toggleBypass()
  {
    this->bypass = !this->bypass;
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
  int volPotPin = A3;
  int tonePotPin = A2;
  int blendPotPin = A4;

  int blendMotorLPin = 44;
  int blendMotorRPin = 45;

  int volMotorLPin = 42;
  int volMotorRPin = 43;

  int toneMotorLPin = 40;
  int toneMotorRPin = 46;

  int gainMotorLPin = 38;
  int gainMotorRPin = 39;

  int headLEDPin = 30;
  int mesaEffectsLEDPin = 31;
  int headEffectsLEDPin = 32;
  int bypassLEDPin = 33;

  int ampSwitchPin = 34;
  int mesaEffectsSwitchPin = 35;
  int headEffectsSwitchPin = 36;
  int cycleChannelSwitchPin = 37;



};

// const int AmpChannel::ORANGE = 0;
// const int AmpChannel::CRUNCH = 1;
// const int AmpChannel::LEAD   = 2;
