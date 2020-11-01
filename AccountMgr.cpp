//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include"AccountMgr.h"

using namespace std;

AccountMgr::~AccountMgr(){
  Account* currentNode = head;
  Account* nextNode;

  while (currentNode != nullptr) {
    nextNode = currentNode->next;
    free(currentNode);
    currentNode = nextNode;
  }

}

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
      AccountMgr::addAccountToList(name, amt);
    }

  }
  else{
    clearScreen();
    cout << "Could not open file debtList.txt. Data not imported." << endl;
  }

}

/// Add the new node to the end of the list
void AccountMgr::addAccountToList(string n, double x){
  if(head == nullptr){
    head = new Account(n, x);
    head->prev = nullptr;
    head->next = nullptr;
    tail = head;
  }
  else{
    Account* temp = head;
    while(temp->next != nullptr){
      temp = temp->next;
    }
    temp->next = new Account(n, x);
    temp->next->next = nullptr;
    temp->next->prev = temp;
    tail = temp->next;
  }
}


void AccountMgr::createAccount(){
  string name;
  double amt;
  Account* temp;

  cout << "Enter a name for the account: ";
  cin.ignore(1000,'\n');
  getline(cin, name);

  //Check if name already exists if there are other accounts
  if (numAccounts != 0){
    temp = findAccount(name);

    while(temp != nullptr){
      cout << "An account with this name already exists." << endl << "Please enter a different name." << endl;

      getline(cin, name);
      temp = findAccount(name);

    }

  }

  cout << "Enter the amount of debt to apply to the account: ";
  cin >> amt;

  while(cin.fail()){  //Validate Input
    cin.clear(); //reset failbit
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> amt;
    cout << "This must be a numeric value. Enter the amount of debt to apply to the account: ";
  }

  addAccountToList(name, amt);
  temp = findAccount(name);
  updateFile("new", 0, temp);
  clearScreen();
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
  Account* temp = head;
  string tempName = makeLowerCase(temp->getName());

  //Make nameChoice all lowercase
  nameChoice = makeLowerCase(nameChoice);

  while(tempName != nameChoice){
    temp = temp->next;

    if(temp == nullptr){
      return nullptr;
    }

    tempName = makeLowerCase(temp->getName());
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


void AccountMgr::displayAccount(Account* temp){
  cout << "Name\t\tAmount Owed" << endl
       << "===================================" << endl
       << fixed << setprecision(2)
       << temp->getName() << "\t\t$" << temp->getAmtOwed() << endl;

  stall2();
}


void AccountMgr::searchByName(){
  //Clear screen
  clearScreen();

  string name;

  cout << "Enter a name to search for: ";
  cin.ignore(1000,'\n');
  getline(cin, name);

  Account* temp = findAccount(name);

  //Check to see if account name exists
  if(temp == nullptr){
    cout << "An account with this name does not exist." << endl;
    stall2();
    return;
  }
  else{ //Display account
    displayAccount(temp);
  }
}


void AccountMgr::changeDebt(string change){

  string nameChoice;
  double amt;

  display();
  cout << "Enter a name from the list: ";
  cin.ignore(1000,'\n');
  getline(cin, nameChoice);

  Account* temp = findAccount(nameChoice);

  //Check to see if account name exists
  while(temp == nullptr){
    cout << "An account with this name does not exist." << endl << "Please enter a name from the list." << endl;

    getline(cin, nameChoice);
    temp = findAccount(nameChoice);

  }

  //Adding debt
  if(change == "add"){

    cout << "Please enter an amount to add to the debt: ";
    cin >> amt;
    Account* temp = findAccount(nameChoice);
    temp->setAmtOwed(temp->getAmtOwed() + amt);
    updateFile(change, amt, temp);
    clearScreen();

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

    clearScreen();

  }
}
