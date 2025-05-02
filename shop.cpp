#include <iostream>
#include <string>
#include <cctype>
#include "utils.h"
#include "menu.h"
using namespace std;

int main()
{
    // Data init
    vector<Stock> stockList;

    // exit if data loading failed
    if (dataInit(stockList) != 0)
        return 1; 

    // Main menu
    mainMenu(stockList);
}
