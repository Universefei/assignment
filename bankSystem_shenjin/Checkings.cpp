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
  // double temp=1.02*amount;                //������ʽ������ȡȡ�����2%������
  double temp = amount;

  if(remittance==remitPost)        //���Ż㣬��ȡ�����5%������
    temp = 1.05*amount;
  else if(remittance==remitCable)  //����㣬��ȡ�����7%������
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

