あ#include "NK_PID.hpp"

Nk_pid::Nk_pid(double kp,double ki,double kd,double freq){
    Kp=kp;
    Ki=ki;
    Kd=kd;
    Freq=freq;
    err[0]=0;
    }
void Nk_pid::SetParam(double Value,double Target){
  err[1]=Target-Value;
  integral+=(err[1]+err[0])/2.0*Freq;
  G_P=err[1];
  G_I=integral;
  G_D=(err[1]-err[0])/Freq;
  err[0]=err[1];
  res+=(Kp*G_P)+(Ki*G_I)+(Kd*G_D);
  res=(res>Max_P)?Max_P:(res<Max_M)?Max_M:res;
}
double Nk_pid::GetGain(double xvalue){
  if(res<0){
    rtn=(res<Max_M)?Max_M:(res>Min_M)?0:res;
      }
  else {
    rtn=(res>Max_P)?Max_P:(res<Min_P)?0:res;
      }
  return (rtn/xvalue);
}
void Nk_pid::SetLimit(double max_p,double min_p,double max_m,double min_m){
  Max_P = max_p*1.0;
  Min_P = min_p*1.0;
  Max_M = max_m*1.0;
  Min_M = min_m*1.0;
}
Nk_pid::~Nk_pid(){}
