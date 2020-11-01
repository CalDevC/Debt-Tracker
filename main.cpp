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
      stall();
    }

    else if(input == "2"){
      mgr->createAccount();
    }

    else if(input == "3"){
      mgr->changeDebt("add");
    }

    else if(input == "4"){
      mgr->changeDebt("remove");
    }

    else if(input == "5"){
      mgr->searchByName();
    }

    else if(input == "q" || input == "Q"){
      //Do nothing but prevent display of "Invalid menu choice"
    }

    else{ //Base Case
      clearScreen();
      cout << "Invalid menu choice.\n\n";
    }
  }

mgr->finishSave();
mgr->~AccountMgr(); //Free list from memory

}

//=====TO-DO=====
//Sort function
//add end node so list can be accessed at the end
//make search not case sensitive
