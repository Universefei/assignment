#ifndef SAVINGS
#define SAVINGS

#include "Account.h"

///
/// can be interpreted as fixed-time deposit account
///
class Savings:public Account
{
public:
  Savings(unsigned accNo, double bal=0.0);
  virtual void withdrawal(double amount);

protected:
  // minimal balance if you wana be a Savings account
  static double minbalance;
};

#endif
