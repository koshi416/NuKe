#ifndef NK_PID
#define NK_PID

class Nk_pid{
public:
  Nk_pid(double kp,double ki,double kd,double freq);//初期設定
  ~Nk_pid();
  void SetParam(double Value,double Target);//現在値、目標値入力
  void SetLimit(double max_p,double min_p,double max_m,double min_m);//正負回転の上下限設定
  double GetGain(double xvalue);//255~-255がデフォルト 割合設定
private:
  double Max_P;
  double Min_P;
  double Max_M;
  double Min_M;
  double Kp;
  double Ki;
  double Kd;
  double Freq;
  double G_P;
  double G_I;
  double G_D;
  double integral;
  double value;
  double target;
  double err[2];
  double res;
  double rtn;
};

#endif
