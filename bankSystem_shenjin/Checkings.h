#ifndef CHECKINGS
#define CHECKINGS

#include "Account.h"

//�������˻�
enum REMIT{
  remitPost,
  remitCable,
  remitOther
}; //�ޣ��Ż㣬���

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
