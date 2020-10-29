//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include "Global.h"
#include <fstream>
using namespace std;

//Global functions
void displayMenu(){
  cout << "============ Main Menu ============"  << endl
       << "   1 - Display all accounts"          << endl
       << "   2 - Add a new account"             << endl
       << "   3 - Add debt to an account"        << endl
       << "   4 - Remove debt from an account"   << endl
       << "   5 - Search for an account"         << endl
       << "   q - Quit"                          << endl
       << "==================================="  << endl
       << "Enter a choice from the list: "       << endl;
}

void stall(){
  cout << "Press enter to continue..." << endl;
  cin.ignore(1000, '\n');
  getline(cin, garbage);
  clearScreen();
}

void stall2(){
  cout << "Press enter to continue..." << endl;
  cin.ignore(1000, '\n');
  clearScreen();
}

void clearScreen(){
  system("clear");
}
