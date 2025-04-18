#include <iostream>
#include "utils.h"
using namespace std;

int main()
{
    // vars
    bool run = true;
    int opt;
    // add classes here ClassName something

    // main loop
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
        cin >> opt;
        cin.ignore();
        switch (opt)
        {
        case 1:
            //show products, give an option to buy and checkout or cancel
            salesMenu();
            break;
        case 2:
            //show stock, give an option to add or remove and cancel
            break;
        case 3:
            clearConsole();
            run = false;
            break;
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }
    } while (run);
}