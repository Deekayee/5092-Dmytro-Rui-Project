#include "utils.h"
#include "stockMenu.h"
#include "salesMenu.h"

void mainMenu(vector<Stock> &stockList);

int main()
{
    // Data init
    vector<Stock> stockList;

    // Exit if data loading failed
    if (dataInit(stockList) != 0)
        return 1;

    // Main menu
    mainMenu(stockList);
}

