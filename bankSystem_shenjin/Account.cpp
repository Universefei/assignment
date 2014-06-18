#include<iostream>
#include "Account.h"

using namespace std;


/// initial default static data member here, not .h file
Account* Account::pFirst=NULL;        //����Ϊ��
int Account::count=0;              //�ʻ�����Ϊ0


/// Constructor
/// ===========
Account::Account(unsigned accNo, double bal)
{
  pNext=NULL;
  acntNumber=accNo;
  balance=bal;
  count++;

  if(!pFirst)
  {
    pFirst=this;
  }
  else
  {
    Account* pS;
    for(pS=pFirst; pS->getNext() ; pS=pS->getNext());//�ҵ����һ�����
    pS->setNext(this);
    //pS->pNext=this;
  };

}

/// Display
/// =======
void Account::displayAll()//��ʾ
{ 
  Account *p = pFirst;
  for(; p; p=p->pNext)
  {
    cout<<"User : "<<p->acntNumber<<endl;
  }
}

/// Deposit
/// =======
void Account::deposit(double amount)//���
{ 
	balance+=amount;  
	//display(); 
}

void Account::setNext(Account* ptmp)
{
  pNext = ptmp;
}


/// AccountNo
/// =========
unsigned Account::accountNo() { return acntNumber; }

/// GetBalance
/// ==========
double Account::getBalance() { return balance; }

/// getFirst
/// ========
Account*& Account::getFirst(){ return pFirst; }

/// getNext
/// =======
Account* Account::getNext(){ return pNext; }

/// NoAccounts
/// ==========
int& Account::noAccounts() { return count; }
