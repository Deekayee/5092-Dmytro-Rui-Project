#pragma once

#include <string>

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

// COLOR RESET
#define RESET "\033[0m"

// UNDERLINE
#define UNDERLINE "\033[4m"

// HORIZONTAL LIMITERS SIZES
#define STOCK_DASH 53
#define PRODUCTS_DASH 59
#define CART_DASH 66

// MAX PRODUCT NAME SIZE
#define STRING_PRODUCT_MAX 22

class Menu
{
public:
    // CONSOLE UTILITY FUNCTIONS
    static void pause();
    static void limh(int n = STOCK_DASH); // assumes default value for stock menu
    static void clearConsole();
    static void setColor(const string &colorCode);
    // VALIDATION FUNCTIONS
    static string Menu::stringToLower(string name);
    static bool validateMenuInput(const string &input, int &opt);
    static int getValidatedInt(const string &prompt, bool zero = false);
    static double getValidatedDouble(const string &prompt);
    static bool promptYESOrNo(string prompt = "Do you wish to continue?");
    static bool promptyesOrNO(string prompt = "Do you wish to continue?");
};