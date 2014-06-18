#include<iostream>
#include "Account.h"
#include "Checkings.h"
using namespace std;

/// Constructors
/// ============
Checkings::Checkings(unsigned accNo, double bal):Account(accNo, bal)
{ 
  remittance=remitOther; 
}

//
/*
Checkings::Checkings(unsigned accNo, double bal, REMIT rd):Account(accNo, bal)
{ 
  remittance=rd; 
}
*/

/// Withdrawal
/// ==========
void Checkings::withdrawal(double amount)
{
  // double temp=1.02*amount;                //其他方式，则收取取款金额的2%手续费
  double temp = amount;

  if(remittance==remitPost)        //若信汇，则取款金额的5%手续费
    temp = 1.05*amount;
  else if(remittance==remitCable)  //若电汇，则取款金额的7%手续费
    temp = 1.02*amount;

  if(balance<temp)
    cout <<"Balance is less than : "<<temp<<endl;
  else
    balance-=temp;
	//display();
}

/// SetRemit
/// ========
void Checkings::setRemit(REMIT rd)
{ 
  remittance=rd; 
}

