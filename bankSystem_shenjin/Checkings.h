#ifndef CHECKINGS
#define CHECKINGS

#include "Account.h"

//结算类账户
enum REMIT{
  remitPost,
  remitCable,
  remitOther
}; //无，信汇，电汇

class Checkings:public Account
{
public:
  Checkings(unsigned accNo, double bal=0.0);
  virtual void withdrawal(double amount);

  // Setter
  void setRemit(REMIT rd);

protected:
  REMIT remittance;
};

#endif
