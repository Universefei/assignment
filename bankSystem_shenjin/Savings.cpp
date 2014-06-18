#include <iostream>
#include "Account.h"
#include "Savings.h"

using namespace std;
// Set minimal balance
double Savings::minbalance=50000.0;     

/// Constructor
/// ===========
Savings::Savings(unsigned accNo, double bal):Account(accNo, bal) 
{}

/// Withdraw
/// ========
void Savings::withdrawal(double amount)
{
  if(balance+minbalance<amount)
    cout <<"balance is less than : " <<amount <<endl;
  else
    balance-=amount;

//	display();
}
