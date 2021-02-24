//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#ifndef ACCOUNTMGR_H
#define ACCOUNTMGR_H

#include "Account.h"

//Controls data structure
class AccountMgr{
protected:
  Account* head;
  Account* tail;
public:

  //Destructor
  ~AccountMgr();

  //Write and Read Functions
  void updateFile(string change, double amt, Account* acct);  //Save updates to debtUpdates.txt
  void finishSave();  //Save list to debtList.txt
  void import();  //Get list from debtList.txt

  //List Altering Functions
  void addAccountToList(string n, double x);  // Add the new node to the end of the list
  void createAccount(); //Initialize a new account object
  void removeAccount(Account**, string n);
  void changeDebt(string change);

  //List Traversing Functions
  Account* findAccount(string nameChoice);
  void searchByName();  //Search for and display a certain Account

  //List Sorting Functions
  void sortList();  //Handles sorting menu
  void bubbleSort(string order);  //Sorts list
  bool getSortType(string type, Account* temp1, Account* temp2);  //Sets how the list is sorted
  void swap(Account* a, Account* b);

  //Display Functions
  void display();
  void displayAccount(Account*);
  void displaySortOptions();

};

#endif
