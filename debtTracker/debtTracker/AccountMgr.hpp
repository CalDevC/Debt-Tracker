//
//  AccountMgr.h
//  debtTracker
//
//  Created by Chase Alexander on 11/1/20.
//  Copyright © 2020 CalDevC. All rights reserved.
//
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

  void display();
  void displayAccount(Account*);  //Search for and display a certain Account
  void searchByName();

};

#endif

