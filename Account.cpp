//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include "Account.h"
#include "Global.cpp"
using namespace std;

Account::Account(string name, double amt){
  this->name = name;
  amtOwed = amt;
  next = nullptr;
  numAccounts++;
}

Account::Account(){
  name = "unknown";
  amtOwed = 0.00;
}

Account::~Account(){}

string Account::getName(){
  return this->name;
}

void Account::setName(string n){
  this->name = n;
}

double Account::getAmtOwed(){
  return amtOwed;
}

void Account::setAmtOwed(double amt){
  amtOwed = amt;
}
