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


void AccountMgr::displaySortOptions(){
  clearScreen();
  cout << "============ Sort List ============"  << endl
       << "   1 - Least to Greatest"             << endl
       << "   2 - Greatest to Least"             << endl
       << "   3 - Alphabetically"                << endl
       << "   r - return to main menu"           << endl
       << "==================================="  << endl
       << "Enter a choice from the list: "       << endl;
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


void AccountMgr::sortList(){
  while(input != "r" && input != "R"){

    displaySortOptions();
    cin >> input;

    if(input == "1"){
      bubbleSort("L->G");
      clearScreen();
      return;
    }

    else if(input == "2"){
      bubbleSort("G->L");
      clearScreen();
      return;
    }

    else if(input == "3"){
      bubbleSort("name");
      clearScreen();
      return;
    }

    else if(input == "r" || input == "R"){
      clearScreen();
      //prevent display of "Invalid menu choice"
    }

    else{ //Base Case
      clearScreen();
      cout << "Invalid menu choice.\n\n";
    }
  }
}

void AccountMgr::bubbleSort(string type){
    if(numAccounts >= 2){
      for(int i = 0; i < numAccounts; i++){

      Account* temp1 = head;
      Account* temp2 = head->next;

      while(temp1->next != nullptr ){

        //Change condition of if staement depending on how the list should be sorted
        if(getSortType(type, temp1, temp2)){
          swap(temp1, temp2);
          temp1 = temp2;
          temp2 = temp1->next;
        }
        else{
          temp1 = temp2;
          temp2 = temp1->next;
        }

      }
    }
  }
  else{
    return;
  }
}

bool AccountMgr::getSortType(string type, Account* temp1, Account* temp2){

  bool sortType;

  if(type == "L->G"){
    sortType = temp1->getAmtOwed() > temp2->getAmtOwed();
  }
  else if(type == "G->L"){
    sortType = temp1->getAmtOwed() < temp2->getAmtOwed();
  }
  else if(type == "name"){
    sortType = makeLowerCase(temp1->getName()) > makeLowerCase(temp2->getName());
  }

  return sortType;
}

/* Swap function that swaps data
void AccountMgr::swap(Account* a, Account* b){
  Account* temp;
  temp->setName(a->getName());
  temp->setAmtOwed(a->getAmtOwed());

  a->setName(b->getName());
  a->setAmtOwed(b->getAmtOwed());

  b->setName(temp->getName());
  b->setAmtOwed(temp->getAmtOwed());

}*/

//Swap function that swaps nodes
void AccountMgr::swap(Account* a, Account* b){
  Account **p1pn;            // & a->prev->next
  Account **p1np;            // & a->next->prev
  Account **p2pn;            // & b->prev->next
  Account **p2np;            // & b->next->prev
  Account *tail;             // only used when x->next == nullptr
  Account *temp;             // temp

  if(head == nullptr || a == nullptr || b == nullptr || a == b)
    return;

  if(head == a)
    p1pn = &head;
  else
    p1pn = &a->prev->next;

  if(head == b)
    p2pn = &head;
  else
    p2pn = &b->prev->next;

  if(a->next == nullptr){
    p1np = &tail;
    tail = a;
  }
  else{
    p1np = &a->next->prev;
  }

  if(b->next == nullptr){
    p2np = &tail;
    tail = b;
  }
  else{
    p2np = &b->next->prev;
  }

  *p1pn = b;
  *p1np = b;
  *p2pn = a;
  *p2np = a;

  temp = a->prev;
  a->prev = b->prev;
  b->prev = temp;

  temp = a->next;
  a->next = b->next;
  b->next = temp;

}


/*  QUICKSORT FUNCTIONS (NOT WORKING)
//Arrange all the elements of the linked list as per the pivot element
Account* AccountMgr::partition(Account* l, Account* h){

  // set pivot as h element
    double x = h->getAmtOwed();

    // similar to i = l-1 for array implementation
    Account *i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Account *j = l; j != h; j = j->next){

      if(j == nullptr){
        break;
      }
      if (j->getAmtOwed() <= x){
        // Similar to i++ for array
        i = (i == NULL)? l : i->next;
        swap(i, j);
      }

    }

    i = (i == NULL)? l : i->next; // Similar to i++
    swap(i, h);
    return i;
}

void AccountMgr::_quickSort(Account* left, Account* right){

  if (right != nullptr && left != nullptr && left != right && left != right->next){
    //cout << op << endl;
    Account* partitionNode = partition(left, right);

    // Separately sort elements before
    // partition and after partition
    _quickSort(left, partitionNode->prev);
    _quickSort(partitionNode->next, right);
  }

}

void AccountMgr::quickSort(){
  _quickSort(head, tail);
}
*/
