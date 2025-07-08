#pragma once //  compiler only sees this lib file once

#include <iostream>

using namespace std;

// COLOR DEFINES
#define Red "\033[0;31m"
#define Green "\033[0;32m"
#define Yellow "\033[0;33m"
#define Blue "\033[0;34m"
#define Magenta "\033[0;35m"
#define Cyan "\033[0;36m"

// COLOR DEFINES - Bright Variant
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

// COLOR DEFINES - BW
#define WHITE "\033[47m"
#define BLACK "\033[30m"

// COLOR RESET
#define RESET "\033[0m"

// UNDERLINE
#define UNDERLINE "\033[4m"

// HORIZONTAL LIMITERS SIZES
#define STOCK_DASH 53
#define CLIENT_DASH 87
#define REPORTS_DASH 56
#define PRODUCTS_DASH 59
#define CART_DASH 66

// MAX PRODUCT NAME SIZE
#define STRING_PRODUCT_MAX 22

// CONSOLE UTILITY FUNCTIONS
void pause();
void limh(int n = STOCK_DASH);
void clearConsole();
void setColor(const string &colorCode);

// VALIDATION FUNCTIONS
bool validateMenuInput(const string &input, int &opt);
int getValidatedInt(const string &prompt, bool zero = false);
double getValidatedDouble(const string &prompt);
string getValidatedAddress();
int getValidatedContact();
string getValidatedName();
string stringToLower(string name);
bool promptYESOrNo(string prompt = "Do you wish to continue?");
bool promptyesOrNO(string prompt = "Do you wish to continue?");
