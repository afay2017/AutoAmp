class AmpChannel
{
private:
  int channel;
  bool Pihrana;
  bool mesaEffects;
  bool headEffects;
public:
  AmpChannel(int channelNumber);
  void setAmpChannel(int channel);
  void setHead(bool Pihrana);
  void setMesaEffects(bool on);
  void setHeadEffects(bool on);
  bool getMesaEffects();
  bool getHeadEffects();
};

AmpChannel::AmpChannel(int channelNumber)
{
 this->channel = channelNumber;
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

void AmpChannel::setHead(bool Pihrana)
{
 this->Pihrana = Pihrana;
}

bool AmpChannel::getHeadEffects()
{
 return (bool)headEffects;
}
