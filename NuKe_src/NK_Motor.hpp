#ifndef NK_Motor
#define NK_Motor

#include "mbed.h"

class Nk_motor{
public:
  Nk_motor(PinName plus,PinName minus,int period);//モーターのピンとデータを送る周波数を設定
  ~Nk_motor();
  void SetLimit(double max,double min);//モーターの正負の最大PWM設定
  void pwmout(double pwm);//pwm出力
private:
  double Max;
  double Min;
  PwmOut *Plus;
  PwmOut *Minus;
  double Pwm;
};

#endif
