#include "utils.h"
#include "stockMenu.h"
#include "salesMenu.h"

int main()
{
    // Data init
    vector<Stock> stockList;
    vector<CartItem> cart;

    // Starting point for file system
    dataInit(stockList);

    // Main menu
    mainMenu(stockList);
}
