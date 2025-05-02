#include "utils.h"
#include "menu.h"

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
