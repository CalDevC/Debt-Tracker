//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include "Account.h"
#include "Global.h"
using namespace std;

//Default Constructor
Account::Account(){
  name = "unknown";
  amtOwed = 0.00;
  next = nullptr;
  numAccounts++;
}

//Constructor
Account::Account(string name, double amt){
  this->name = name;
  amtOwed = amt;
  next = nullptr;
  numAccounts++;
}

//Destructor
Account::~Account(){}

//Getter Functions
string Account::getName(){
  return this->name;
}

double Account::getAmtOwed(){
  return this->amtOwed;
}

//Setter Functions
void Account::setName(string name){
  this->name = name;
}

void Account::setAmtOwed(double amt){
  amtOwed = amt;
}
