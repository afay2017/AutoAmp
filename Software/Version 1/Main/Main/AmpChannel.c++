class AmpChannel
{
private:
  int channel;
  int head;
  bool mesaEffects;
  bool headEffects;
public:
  AmpChannel(int channelNumber);
  void setAmpChannel(int channel);
  void setHead(int head);
  void setMesaEffects(bool on);
  void setHeadEffects(bool on);
  bool getMesaEffects();
  bool getHeadEffects();
};

AmpChannel::AmpChannel(int channelNumber)
{
  channel = channelNumber;
}


void AmpChannel::setAmpChannel(int channelNumber)
{
 channel = channelNumber;
}

void AmpChannel::setMesaEffects(bool on)
{
 mesaEffects = on;
}

void AmpChannel::setHeadEffects(bool on)
{
 headEffects = on;
}

bool AmpChannel::getMesaEffects()
{
 return (bool)mesaEffects;
}

bool AmpChannel::getHeadEffects()
{
 return (bool)headEffects;
}
