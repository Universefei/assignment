#ifndef ACCOUNT
#define ACCOUNT

class Account
{

public:
  // Constructor
  Account(unsigned accNo, double bal=0.0);
  
  // geter and setter
  unsigned accountNo(); 
  double getBalance();
  static Account*& getFirst();
  Account* getNext();
  static int &noAccounts();

  void setNext(Account* p);
  static void displayAll();

  // Operations
  void deposit(double amount);
  virtual void withdrawal(double amount)=0;

protected:
  // List utilities
  static Account* pFirst;
  Account* pNext;

  // Number of accounts
  static int count;

  unsigned acntNumber;
  double balance;

  // log file
//  static ifstream logFile;
};

#endif
