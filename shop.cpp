#include <iostream>
#include <string>
#include <cctype>
#include "utils.h"
#include "menu.h"
using namespace std;

void test()
{
    // Stock testStock(12,"TESTE",1,2.50);
    // string testString = testStock.toString();
    // cout << testString;
    createStockFile();
    vector <Stock> *StockList;
    bool flag = openStockFile(StockList);
    addPurchaseToStock(StockList);
    cin.ignore();
    return;

}

int main()
{
    // vars
    bool run = true;
    int opt;
    string input;
    //test();
    // add classes (when checking out, so the time stamps are correct) ClassName something

    // main loop
    cout << "Opening Stock File... ";
    createStockFile();
    vector <Stock> stockList;
    if(openStockFile(&stockList))
    {
        cout << "Success!" << endl;
        pause();
    }else 
    {
        cout << "Error" << endl;
        pause();
        return 1;
    }
    
    
    do
    {
        do
        {
            clearConsole();
            cout << "Shop menu" << endl;
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
            stockMenu(&stockList);
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