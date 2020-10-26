//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


//Global Variables
string input = "";
string garbage;
int numAccounts = 0;

//Class definition
class Account{
private:
  string name;
  double amtOwed;
public:
  Account* next;

  Account(string name, double amt){
    this->name = name;
    amtOwed = amt;
    next = nullptr;
    numAccounts++;
  }

  Account(){
    name = "unknown";
    amtOwed = 0.00;
    numAccounts++;
  }

  string getName(){
    return this->name;
  }

  void setName(string n){
    this->name = n;
  }

  double getAmtOwed(){
    return amtOwed;
  }

  void setAmtOwed(double amt){
    amtOwed = amt;
  }
};


//Template functions
void displayMenu();
void stall();
void startSave();

//Class definition
class AccountMgr{
private:
  Account* head;
  Account* tail;
public:

  void updateFile(string change, double amt, Account* acct){
    fstream myFile("debtUpdates.txt", ios::out | ios::app);
    if(myFile.is_open()){

    //Adding debt
      if(change == "add"){

        myFile << __TIME__ << ": Added " << amt << " to " << acct->getName() << "'s debt for a total of " << acct->getAmtOwed() << endl;

      }
    //Removing debt
      else if(change == "remove"){

        myFile << __TIME__ << ": Removed " << amt << " to " << acct->getName() << "'s debt for a total of " << acct->getAmtOwed() << endl;

      }
    //New account added
      else if(change == "new"){

        myFile << __TIME__ << ": Account created for " << acct->getName() << " with a debt of " << acct->getAmtOwed() << endl;

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
  void finishSave(){

    system("clear");

    fstream myFile("debtList.txt", ios::out | ios::trunc);
    if(myFile.is_open()){

      myFile << "Last updated " << __DATE__ << ": " << endl;

      if(numAccounts != 0){
        Account* temp = head;
        myFile << "Name\t\tAmount Owed" << endl << "===================================" << endl;
        while(temp != nullptr){
          myFile << temp->getName() << "\t\t" << temp->getAmtOwed() << endl;
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
  void import(){

    fstream myFile("debtList.txt", ios::in);
    if(myFile.is_open()){
      string name = "";
      double amt = 0.00;

      myFile.ignore(1000, '\n');
      myFile.ignore(1000, '\n');
      myFile.ignore(1000, '\n');

      while (myFile >> name >> amt) {
        cout << name << "     " << amt << endl;
        addAccount(name, amt);
      }

    }
    else{
      system("clear");
      cout << "Could not open file debtList.txt. Data not imported." << endl;
    }

  }

  /// Add the new node to the end of the list
  void addAccount(string n, double x){
    if(head == nullptr){
      head = new Account(n, x);
      updateFile("new", 0, head);
    }
    else{
      Account* temp = head;
      while(temp->next != nullptr){
        temp = temp->next;
      }
      temp->next = new Account(n, x);
      updateFile("new", 0, temp->next);
    }
  }


  Account* findAccount(string nameChoice){
    Account* temp = new Account;
    temp = head;
    while(temp->getName() != nameChoice){
      temp = temp->next;
    }

    return temp;
  }


  void display(){
    //Clear screen
    system("clear");

    if(numAccounts == 0){ //Handle if no accounts
      cout << "No accounts to display." << endl;
    }
    else{
      Account* temp = head;
      cout << "Name\t\tAmount Owed" << endl << "===================================" << endl;
      while(temp != nullptr){
        cout << temp->getName() << "\t\t" << temp->getAmtOwed() << endl;
        temp = temp->next;
      }
    }
  }


  void changeDebt(string change){
    string nameChoice;
    double amt;
    display();
    cout << "Enter a name from the list: ";
    cin.ignore();
    getline(cin, nameChoice);

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


  // Use Bubble Sort to sort the list
  void sortList(){
    //Get number of elements in list
    int listSize = 1;
    Account* temp = head;
    while(temp->next != nullptr){
      temp = temp->next;
      listSize++;
    }
    //Sort list
    for(int i = 0; i < listSize; i++){
      Account* temp1 = head;
      Account* temp2 = head->next;
      int temp3 = 0;
      while(temp1->next != nullptr){
        if(temp1->getAmtOwed() > temp2->getAmtOwed()){
          temp3 = temp1->getAmtOwed();
          temp1->setAmtOwed(temp2->getAmtOwed());
          temp2->setAmtOwed(temp3);
          temp1 = temp2;
          temp2 = temp2->next;
        }
        else if(temp1->getAmtOwed() <= temp2->getAmtOwed()){
          temp1 = temp2;
          temp2 = temp1->next;
        }
      }
    }
  }


  /// The list must be sorted before calling this function
  void removeDuplicatedNodes(){
    Account* temp1 = head;
    Account* temp2;
    if (temp1 == nullptr)
      return;

    while (temp1->next != nullptr){
      if (temp1->getAmtOwed() == temp1->next->getAmtOwed()){
        temp2 = temp1->next->next;
        free(temp1->next);
        temp1->next = temp2;
      }
      else{
        temp1 = temp1->next;
      }
    }
  }

};



/*================================Main Function===============================*/
int main(){
  AccountMgr* mgr;
  mgr->import();
  startSave();

  while(input != "q" && input != "Q"){
    displayMenu();

    cin >> input;

    if(input == "1"){

      mgr->display();
      stall();

    }
    else if(input == "2"){

      string name;
      double amt;
      cout << "Enter a name for the account: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter the amount of debt to apply to the account: ";
      cin >> amt;
      //Validate Input
      while(cin.fail()){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cin >> amt;
        cout << "This must be a numeric value. Enter the amount of debt to apply to the account: ";
      }
      mgr->addAccount(name, amt);

    }
    else if(input == "3"){

      mgr->changeDebt("add");

    }
    else if(input == "4"){

      mgr->changeDebt("remove");

    }
    else if(input == "q" || input == "Q"){
      //Do nothing but prevent display of "Invalid menu choice"
    }
    else{

      cout << "Invalid menu choice.";

    }
  }

mgr->finishSave();

}



/*=============================Function definitions===========================*/
void displayMenu(){
  system("clear");  //Clear screen
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
}

void startSave(){
  fstream myFile("debtUpdates.txt", ios::out | ios::app);
  if(myFile.is_open()){

    myFile << "Update from " << __DATE__ << ": " << endl;

    myFile.close();

  }
  else{
    system("clear");
    cout << "Could not open file debtUpdates.txt. Data not saved." << endl;
  }
}

//error checking for name and amt
//abstraction for getting name and amt to add/remove (changeDebt and have choice between add and subtract)
//Fix prompt when subtracting debt from an acct
