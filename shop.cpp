#include <iostream>
#include <string>
#include <cctype>
#include "utils.h"
#include "menu.h"
using namespace std;

int main()
{
    // Data init
    cout << "Opening Stock File... ";
    createStockFile();
    vector<Stock> stockList;
    if (openStockFile(&stockList))
    {
        cout << "Success!" << endl;
        pause();
    }
    else
    {
        cout << "Error" << endl;
        pause();
        return 1;
    }

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