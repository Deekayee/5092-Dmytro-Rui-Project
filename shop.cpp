#include "utils.h"
#include "stockMenu.h"
#include "salesMenu.h"

int main()
{
    // Data init
    vector<Stock> stockList;
    vector<CartItem> cart;

    


    // Exit if data loading failed
    if (dataInit(stockList) != 0)
        return 1;

    // Main menu
    mainMenu(stockList);
}
