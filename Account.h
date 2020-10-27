//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
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
