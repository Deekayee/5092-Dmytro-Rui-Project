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

void mainMenu(vector<Stock> &stockList)
{
    // main loop
    // vars
    bool run = true;
    int opt;
    string input;

    do
    {
        do
        {
            clearConsole();
            setColor("\033[0;36m");
            cout << "Shop menu" << endl;
            setColor("\033[0m");
            limh();
            cout << "1. Shop Sales" << endl;
            limh();
            cout << "2. Shop Stock" << endl;
            limh();
            cout << "3. Exit" << endl;
            limh();
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            // show products, give an option to buy and checkout or cancel
            salesMenu();
            break;
        case 2:
            // show stock, give an option to add or remove and cancel
            stockMenu(stockList);
            break;
        case 3:
            // exit
            clearConsole();
            run = false;
            break;
        default:
            // user is a bit slow, what can we do
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }
    } while (run);
}