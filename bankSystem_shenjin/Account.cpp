#include<iostream>
#include "Account.h"

using namespace std;


/// initial default static data member here, not .h file
Account* Account::pFirst=NULL;        //链表为空
int Account::count=0;              //帐户个数为0


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
    for(pS=pFirst; pS->getNext() ; pS=pS->getNext());//找到最后一个结点
    pS->setNext(this);
    //pS->pNext=this;
  };

}

/// Display
/// =======
void Account::displayAll()//显示
{ 
  Account *p = pFirst;
  for(; p; p=p->pNext)
  {
    cout<<"User : "<<p->acntNumber<<endl;
  }
}

/// Deposit
/// =======
void Account::deposit(double amount)//存款
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
