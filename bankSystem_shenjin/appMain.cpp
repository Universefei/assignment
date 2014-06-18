#include <iostream>
#include "common.h"
#include <typeinfo>


using namespace std;

class Account;
class Checkings;
class Savings;
/// log files.
//ofstream logFile(LOGFILE);
//ofstream Account::logFile = logFile;

/// Prompt functions
void showStartMenu()
{
  cout<<"======================================================="<<endl;
  cout<<"Start Menu"<<endl;
  Account::displayAll();
  cout<<"-------------------------------------------------------"<<endl;
  cout<<"chosing operations:"<<endl;
  cout<<"c --> Create account"<<endl;
  cout<<"l --> Login account"<<endl;
  cout<<"q --> Quit"<<endl;
}

void showLogedMenu(Account *pLogin)
{
  cout<<"======================================================="<<endl;
  cout<<"You are loged in successfully!"<<endl;
  cout<<"-------------------------------------------------------"<<endl;
  cout<<"Account Number : "<<pLogin->accountNo()<<endl;
  if(dynamic_cast<Checkings *>(pLogin))
    cout<<"Account type   : Checkings"<<endl;
  else
    cout<<"Account type   : Savings"<<endl;
  cout<<"Account balance: "<<pLogin->getBalance()<<endl;
  cout<<"-------------------------------------------------------"<<endl;
  cout<<"chose operation:"<<endl;
  cout<<"d --> Deposit money"<<endl;
  cout<<"w --> Withdraw money"<<endl;
  cout<<"q --> Logout"<<endl;
}

/// atCreateAcc
/// ===========
void atCreateAcc()
{
  char typeOpt;
  unsigned accNo;
  double bal;

  /// chosing account type
  do
  {
    cout<<"input your account type"<<endl;
    cout<<"c --> Checking"<<endl;
    cout<<"s --> saving"<<endl;
    cin>>typeOpt;
  }while(typeOpt !='c' && typeOpt != 's');

  /// Judging is usr's account Number duplicated
  bool noDuplicated = false;
  Account* pt;
  while(!noDuplicated)
  {
    cout<<"input your account number"<<endl;
    cin>>accNo;
    for(pt=Account::getFirst(); pt; pt=pt->getNext())
    {
      if(pt->accountNo() == accNo)
      {
        noDuplicated = false;
        cout<<"this ID was occupied, try another one"<<endl;
        break;
      }
    }
    if(pt==NULL) 
      noDuplicated = true;
  }

  /// deposit money
  cout<<"input your balance"<<endl;
  cin>>bal;

  /// Real create corresponding data structure in internal storage
  if(typeOpt == 'c')
  {
    //Checkings *p = new Checkings(accNo, bal);
    new Checkings(accNo, bal);
  }
  else if(typeOpt == 's')
  {
    new Savings(accNo, bal);
  }

}

/// Find account
Account* findAcc(unsigned accNo)
{
  Account* ptmp = Account::getFirst();
  for( ; ptmp ; ptmp=ptmp->getNext())
  {
    if(ptmp->accountNo() == accNo)
      return ptmp;
  }
  cout<<"account Number does not exsit!"<<endl;
  return ptmp;
}

/// atLoginAcc
/// ==========
void atLoginAcc()
{
  unsigned accNo;
  Account* pLogin;

  
  /// input a valid user account Number
  do
  {
    cout<<"input your account Number"<<endl;
    cin>>accNo;
    pLogin = findAcc(accNo);
  }
  while(!pLogin);



  /// all loged in operation are all in this loop
  while(1)
  {
    cout<<"beging loop"<<endl;
    char opt;
    showLogedMenu(pLogin);

    cin>>opt;
    /// Logout
    if(opt == 'q')
    {
      return;
    }
    /// Deposit
    else if(opt == 'd')
    {
 
      double depositAmt;
      cout<<"input deposit amount : "<< endl;
      cin>>depositAmt;

      pLogin->deposit(depositAmt);
    }
    /// withdraw
    else if(opt == 'w')
    {
      char checkType;
      double withdrawAmt;
      
      // prompt for user interface
      cout<<"input withdraw amount : "<< endl;
      cin>>withdrawAmt;

      // If login account is Checkings, ask for remit type, and set corresponding member
      Checkings* pCast = dynamic_cast<Checkings *>(pLogin);
      if(pCast)
      {
        do
        {
          cout<<"input checking type : "<<endl;
          cout<<"----------------------"<<endl;
          cout<<"p --> Post"<<endl;
          cout<<"c --> Cable"<<endl;
          cout<<"n --> normal"<<endl;
          cin>>checkType;
        }
        while(checkType !='p' &&
            checkType != 'c' &&
            checkType != 'n');

        // set remit
        //TODO: need dynamic_cast to derived class pointer here;
        if(checkType == 'p')
        {
          pCast->setRemit(remitPost);
        }
        else if(checkType == 'c')
        {
          pCast->setRemit(remitCable);
        }
        else if(checkType == 'n')
        {
          pCast->setRemit(remitOther);
        }
      }

      pLogin->withdrawal(withdrawAmt);
    }
    /// user input error
    else
    {
      cout<<"input error, try again"<<endl;
    }
  }
}

/*****************************************************************************
 *                                     mian                                  *
 *****************************************************************************/

int main()
{
  // Record user's operation optition;
  char opt;

  while(true)
  {
    showStartMenu();
    cin>>opt;

    if(opt == 'c')
    {
      atCreateAcc();
    }
    else if(opt == 'l')
    {
      atLoginAcc();
    }
    else if(opt == 'q')
    {
      return 0;
    }
    else
    {
      cout<<"input error, try again"<<endl;
    }
  }

}

