//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include "Global.h"
using namespace std;

class Account{
private:
  //Private Variables
  string name;
  double amtOwed;
public:
  //Constructors and destructors
  Account();
  Account(string name, double amt);
  ~Account();

  //Public Variables
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
