//
//  Global.h
//  debtTracker
//
//  Created by Chase Alexander on 11/1/20.
//  Copyright © 2020 CalDevC. All rights reserved.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#include<string>
using namespace std;

//Global Variables
string input = "";
string garbage;
int numAccounts = 0;

//Template functions
void displayMenu();
void clearScreen();
string makeLowerCase(); //Converts a string to all lowercase
void stall();
void stall2();

#endif
