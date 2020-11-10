//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#ifndef ACCOUNTMGR_H
#define ACCOUNTMGR_H

#include "Account.cpp"

//Controls data structure
class AccountMgr{
protected:
  Account* head;
  Account* tail;
public:

  ~AccountMgr();  //Destructor

  void updateFile(string change, double amt, Account* acct);  //Save debt to debtList.txt
  void finishSave();  //Get info from debtList.txt
  void import();

  void addAccountToList(string n, double x);  // Add the new node to the end of the list
  void createAccount(); //Initialize a new account object
  void removeAccount(Account**, string n);
  Account* findAccount(string nameChoice);
  void changeDebt(string change);

  void sortList();
  void quickSort(string op);
  void _quickSort(Account* l, Account* h, string op);
  Account* partition(Account* l, Account* h, string op);
  void swap(Account* a, Account* b);

  void display();
  void displayAccount(Account*);  //Search for and display a certain Account
  void searchByName();
  void displaySortOptions();

};

#endif
