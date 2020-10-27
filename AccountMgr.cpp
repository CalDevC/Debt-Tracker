//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include"AccountMgr.h"
using namespace std;

void AccountMgr::updateFile(string change, double amt, Account* acct){
  fstream myFile("debtUpdates.txt", ios::out | ios::app);
  if(myFile.is_open()){

  //Adding debt
    if(change == "add"){
      myFile << fixed << setprecision(2) << __TIME__ << ": Added " << amt << " to " << acct->getName() << "'s debt for a total of $" << acct->getAmtOwed() << endl;

    }
  //Removing debt
    else if(change == "remove"){
      myFile << fixed << setprecision(2) << __TIME__ << ": Removed " << amt << " to " << acct->getName() << "'s debt for a total of $" << acct->getAmtOwed() << endl;

    }
  //New account added
    else if(change == "new"){
      myFile << fixed << setprecision(2) << __TIME__ << ": Account created for " << acct->getName() << " with a debt of $" << acct->getAmtOwed() << endl;

    }

    myFile.close();
  }
  //If can't open file
  else{
    system("clear");
    cout << "Could not open file debtUpdates.txt. Data not saved." << endl;
  }
}

//Save debt to debtList.txt
void AccountMgr::finishSave(){

  system("clear");

  fstream myFile("debtList.txt", ios::out | ios::trunc);
  if(myFile.is_open()){

    myFile << "Last updated " << __DATE__ << ": " << endl;

    if(numAccounts != 0){
      Account* temp = head;
      myFile << "Name\t\tAmount Owed" << endl << "===================================" << endl;
      while(temp != nullptr){
        myFile << fixed << setprecision(2) << temp->getName() << "\t\t" << temp->getAmtOwed() << endl;
        temp = temp->next;
      }
    }

    myFile.close();

    cout << "Data saved to file debtList.txt" << endl;

  }
  else{
    system("clear");
    cout << "Could not open file debtList.txt. Data not saved." << endl;
  }
}

//Get info from debtList.txt
void AccountMgr::import(){

  fstream myFile("debtList.txt", ios::in);
  if(myFile.is_open()){
    string name = "";
    double amt = 0.00;

    for(int i = 0; i < 3; i++){
      myFile.ignore(1000, '\n');
    }

    while (myFile >> name >> amt) {
      AccountMgr::addAccount(name, amt);
    }

  }
  else{
    system("clear");
    cout << "Could not open file debtList.txt. Data not imported." << endl;
  }

}

/// Add the new node to the end of the list
void AccountMgr::addAccount(string n, double x){
  if(head == nullptr){
    head = new Account(n, x);
    head->prev = nullptr;
    updateFile("new", 0, head);
  }
  else{
    Account* temp = head;
    while(temp->next != nullptr){
      temp = temp->next;
    }
    temp->next = new Account(n, x);
    temp->prev = temp;
    updateFile("new", 0, temp->next);
  }
}


Account* AccountMgr::findAccount(string nameChoice){
  Account* temp = new Account;
  temp = head;

  while(temp->getName() != nameChoice){
    temp = temp->next;

    if(temp == nullptr){
      return nullptr;
    }
  }

  return temp;
}


void AccountMgr::display(){
  //Clear screen
  system("clear");

  if(numAccounts == 0){ //Handle if no accounts
    cout << "No accounts to display." << endl;
  }
  else{
    Account* temp = head;
    cout << "Name\t\tAmount Owed" << endl << "===================================" << endl;
    while(temp != nullptr){
      cout << fixed << setprecision(2) << temp->getName() << "\t\t$" << temp->getAmtOwed() << endl;
      temp = temp->next;
    }
  }
}


void AccountMgr::changeDebt(string change){

  string nameChoice;
  double amt;

  display();
  cout << "Enter a name from the list: ";
  cin.ignore(1000,10);
  getline(cin, nameChoice);

  //Check to see if account name exists
  while(AccountMgr::findAccount(nameChoice) == nullptr){
    cout << "An account with this name does not exist." << endl << "Please enter a name from the list." << endl;

    getline(cin, nameChoice);

  }

  //Adding debt
  if(change == "add"){

    cout << "Please enter an amount to add to the debt: ";
    cin >> amt;
    Account* temp = findAccount(nameChoice);
    temp->setAmtOwed(temp->getAmtOwed() + amt);
    updateFile(change, amt, temp);

  }
  //Removing debt
  else if(change == "remove"){

    cout << "Please enter an amount to remove form the debt: ";
    cin >> amt;
    Account* temp = findAccount(nameChoice);
    temp->setAmtOwed(temp->getAmtOwed() - amt);
    updateFile(change, amt, temp);

  }
}
