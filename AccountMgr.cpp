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
      myFile << fixed << setprecision(2) << __DATE__ << " - " << __TIME__ << ": Added " << amt << " to " << acct->getName() << "'s debt for a total of $" << acct->getAmtOwed() << endl;

    }
  //Removing debt
    else if(change == "remove"){
      myFile << fixed << setprecision(2) << __DATE__ << " - " << __TIME__ << ": Removed " << amt << " from " << acct->getName() << "'s debt for a total of $" << acct->getAmtOwed() << endl;

    }
  //New account added
    else if(change == "new"){
      myFile << fixed << setprecision(2) << __DATE__ << " - " << __TIME__ << ": Account created for " << acct->getName() << " with a debt of $" << acct->getAmtOwed() << endl;

    }
  //Account Deleted
    else if(change == "delete"){
      myFile << fixed << setprecision(2) << __DATE__ << " - " << __TIME__ << ": Account deleted for " << acct->getName() << endl;
    }

    myFile.close();
  }
  //If can't open file
  else{
    clearScreen();
    cout << "Could not open file debtUpdates.txt. Data not saved." << endl;
  }
}

//Save debt to debtList.txt
void AccountMgr::finishSave(){

  clearScreen();

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
    clearScreen();
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
    clearScreen();
    cout << "Could not open file debtList.txt. Data not imported." << endl;
  }

}

/// Add the new node to the end of the list
void AccountMgr::addAccount(string n, double x){
  if(head == nullptr){
    head = new Account(n, x);
    head->prev = nullptr;
    //updateFile("new", 0, head);
  }
  else{
    Account* temp = head;
    while(temp->next != nullptr){
      temp = temp->next;
    }
    temp->next = new Account(n, x);
    temp->next->prev = temp;
    //updateFile("new", 0, temp->next);
  }
}


void AccountMgr::removeAccount(Account** head_ref, string n){

  Account* temp1 = findAccount(n);

  //base case
    if (*head_ref == nullptr || temp1 == nullptr)
        return;

    //If node to be removed is head node
    if (*head_ref == temp1)
        *head_ref = temp1->next;

    //Change next only if node to be removed is not the last node
    if (temp1->next != nullptr)
        temp1->next->prev = temp1->prev;

    //Change prev only if node to be removed is not the first node
    if (temp1->prev != nullptr)
        temp1->prev->next = temp1->next;

    updateFile("delete", 0, temp1);
    free(temp1);  //free the memory occupied by removed node
    numAccounts--;  //Deincrement number of accounts
    return;

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
  clearScreen();

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
  cin.ignore(1000,'\n');
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

    if(temp->getAmtOwed() == 0.00){
      removeAccount(&head, temp->getName());
    }

  }
}
