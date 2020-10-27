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
       << "   q - Quit"                          << endl
       << "==================================="  << endl
       << "Enter a choice from the list: "       << endl;
}

void stall(){
  cout << "Press enter to continue..." << endl;
  cin.ignore();
  getline(cin, garbage);
  clearScreen();
}

void clearScreen(){
  system("clear");
}

void startSave(){
  fstream myFile("debtUpdates.txt", ios::out | ios::app);
  if(myFile.is_open()){

    myFile << "Update from " << __DATE__ << ": " << endl;

    myFile.close();

  }
  else{
    clearScreen();
    cout << "Could not open file debtUpdates.txt. Data not saved." << endl;
  }
}
