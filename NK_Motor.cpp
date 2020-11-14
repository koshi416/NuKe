#include "NK_Motor.hpp"

Nk_motor::Nk_motor(PinName plus,PinName minus,int period){
  Plus = new PwmOut(plus);
  Minus = new PwmOut(minus);
  Plus->period_us(period);
  Minus->period_us(period);
}
Nk_motor::~Nk_motor(){
}
void Nk_motor::SetLimit(double max,double min){
  Max = max;
  Min = min;
}
void Nk_motor::pwmout(double pwm){
    Pwm=(pwm>Max)?Max:(pwm<Min)?Min:pwm;
    if(Pwm<0.0){
        *Minus=Pwm*-1;
    }
    else {
        *Plus=Pwm;
    }
}
