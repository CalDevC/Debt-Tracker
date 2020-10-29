//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#include"AccountMgr.cpp"

int main(){

  AccountMgr* mgr;  //Create manager object

  mgr->import();  //Import the current list saved in debtList.txt

  //Loop menu choices until user decides to quit
  while(input != "q" && input != "Q"){

    displayMenu();
    cin >> input;

    if(input == "1"){

      mgr->display();
      
    }
    else if(input == "2"){

      string name;
      double amt;

      cout << "Enter a name for the account: ";
      cin.ignore(1000,'\n');
      getline(cin, name);

      //Check if name already exists if there are other accounts
      if (numAccounts != 0){
        while(mgr->findAccount(name) != nullptr){
          cout << "An account with this name already exists." << endl << "Please enter a different name." << endl;

          getline(cin, name);

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

      mgr->addAccount(name, amt);
      mgr->updateFile("new", 0, mgr->findAccount(name));
      clearScreen();

    }
    else if(input == "3"){

      mgr->changeDebt("add");
      clearScreen();

    }
    else if(input == "4"){

      mgr->changeDebt("remove");
      clearScreen();

    }
    else if(input == "5"){

      mgr->displayAccount();

    }
    else if(input == "q" || input == "Q"){
      //Do nothing but prevent display of "Invalid menu choice"
    }
    else{

      clearScreen();
      cout << "Invalid menu choice.\n\n";

    }
  }

mgr->finishSave();

}

//=====TO-DO=====
//5th option to check debt for a certain name
//Sort function
//Abstraction for option 2 in main
