//
//  Account.h
//  debtTracker
//
//  Created by Chase Alexander on 11/1/20.
//  Copyright © 2020 CalDevC. All rights reserved.

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Global.cpp"
using namespace std;

class Account{
private:
  string name;
  double amtOwed;
public:
  Account();
  Account(string name, double amt);
  ~Account();

  Account* next;
  Account* prev;

  //Getter functions
  string getName();
  double getAmtOwed();

  //Setter functions
  void setName(string n);
  void setAmtOwed(double amt);
};

#endif