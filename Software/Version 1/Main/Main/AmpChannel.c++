class AmpChannel
{
private:
  int channel;
  int head;
  bool mesaEffects;
public:
  AmpChannel(int channelNumber);
  void setAmpChannel(int channel);
  void setHead(int head);
  void setMesaEffects(bool on);
  void setHeadEffects(bool on);
  bool getMesaEffects();
};

AmpChannel::AmpChannel(int channelNumber)
{
  channel = channelNumber;
}


void AmpChannel::setAmpChannel(int channelNumber)
{
 channel = channelNumber;
}


bool AmpChannel::getMesaEffects()
{
 return (bool)mesaEffects;
}
