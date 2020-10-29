//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#ifndef ACCOUNTMGR_H
#define ACCOUNTMGR_H

#include "Account.cpp"

//Controls data structure
class AccountMgr{
private:
  Account* head;
public:

  void updateFile(string change, double amt, Account* acct);//Save debt to debtList.txt
  void finishSave();//Get info from debtList.txt
  void import();
  void addAccount(string n, double x);// Add the new node to the end of the list
  void removeAccount(Account**, string n);
  Account* findAccount(string nameChoice);
  void display();
  void displayAccount();//Search for and display a certain Account
  void changeDebt(string change);

};

#endif
