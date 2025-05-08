#pragma once //  compiler only sees this lib file once
#include <iostream>  // will need this for cin and cout
#include <string>    // will need this for the string class
#include <fstream>   // will need this for file handling
#include <sstream>   // will need this for string stream
#include <algorithm> // will need this for sorting and searching
#include <vector>    // will need for stock vector list
#include <regex>     // will need this for regex validation

#include "shopClasses.h" // my classes
using namespace std;

//COLOR DEFINES
#define Red "\033[0;31m"
#define Green "\033[0;32m"
#define Yellow "\033[0;33m"
#define Blue "\033[0;34m"
#define Magenta "\033[0;35m"
#define Cyan "\033[0;36m"

//COLOR DEFINES - Bright Variant
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

//COLOR RESET
#define RESET "\033[0m"

//CONSOLE UTILITY FUNCTIONS
void pause();
void limh(int n);
void clearConsole();
void setColor(const string &colorCode);

//VALIDATION FUNCTIONS
bool validateMenuInput(const string &input, int &opt);
int getValidatedInt(const string &prompt);
double getValidatedDouble(const string &prompt);
string  stringToLower(string name);

//FILE FUNCTIONS
void writeToFile(string filename, const string &line);
void createStockFile();
bool openStockFile(vector<Stock> *stockList);
bool updateFile(vector<Stock> &stockList);
int dataInit(vector<Stock> &stockList);

//STOCK FUNCTIONS
void addPurchaseToStock(vector<Stock> &stockList);
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *&item, const string &name);
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *&item, int id);
vector<Stock> searchForProduct(vector<Stock> &stockList, const string &name);
bool showSearchResults(vector<Stock> items);
bool removePurchaseFromStock(vector<Stock> &stockList, int id);
void changePurchaseFromStock(vector<Stock> &stockList, Stock *olditem, Stock newitem);
void printStock(const vector<Stock> &stockList, const string &title, vector<int> idColor, const string colorCode);
void printStock(const vector<Stock> &stockList, const string &title);
