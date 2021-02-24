//Debt Tracker
//Author: Chase Alexander
//MacOS Version (Bash)

#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
using namespace std;

//Global Variables
static string garbage;
static string input = "";
static int numAccounts = 0;

//Template functions
void displayMenu();
string makeLowerCase(string); //Converts a string to all lowercase
void stall();
void stall2();
void clearScreen();

#endif
