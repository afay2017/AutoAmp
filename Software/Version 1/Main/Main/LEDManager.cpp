  #include <Arduino.h>
class LEDManager
{
private:
  int channel;
  int head;
  bool mesaEffects;
  bool headEffects;
  int bypassPin = 1;
  int headPin = 1;
  int mesaEffectsPin = 1;
  int headEffectsPin = 1;
  int leadPin = 1;
public:
  void setChannel(int channel);
  void setHead(int head);
};

void LEDManager::setMesaEffects(bool on)
{
 this->mesaEffects = on;
}

bool LEDManager::getMesaEffects()
{
 return (bool)mesaEffects;
}

void LEDManager::setHeadEffects(bool on)
{
 this->headEffects = on;
}

bool LEDManager::getHeadEffects()
{
 return (bool)headEffects;
}

void LEDManager::setHead(int head)
{
 this->head = head;
}

bool LEDManager::getHead()
{
 return (bool)head;
}
