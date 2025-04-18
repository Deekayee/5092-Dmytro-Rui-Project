#include <iostream>
#include <string> // will need this for the string class
#include <fstream> // will need this for file handling
#include <sstream> // will need this for string stream 
#include <cctype> // will need this for character validations
#include <algorithm> // will need this for sorting and searching
#include <cstdlib>  // for clearing the console

#include "shopClasses.h" // my classes
using namespace std;

void limh() // horizontal line
{
    cout << "----------------------------------------" << endl;
}

void clearConsole() // clear the console
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}

void pause() // pause the console
{
    cout << "Press enter to continue...";
    cin.ignore();
}

// Sales Menu
void salesMenu()
{
    bool salesMenu = true;
    int salesOpt;
    do
    {
        clearConsole();
        cout << "Sales Menu" << endl;
        limh();
        cout << "1. Show Products" << endl;
        limh();
        cout << "2. Go Back" << endl;
        limh();
        cout << "Option: ";
        cin >> salesOpt;
        cin.ignore();

        switch (salesOpt)
        {
        case 1:
            cout << "Products" << endl;
            limh();
            // show products
            break;
        case 2: // TODO
            salesMenu = false;
            break;
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }

    } while (salesMenu);
}

// Products Menu
void productsMenu() // TODO
{
    bool productsMenu = true;
    int productsOpt;
    do
    {
        clearConsole();
        // function to show products as selectable options, when selected, show more details and give option to add to cart (input quantity here), checkout or cancel
        limh();

        cin >> productsOpt;
        cin.ignore();

    } while (productsMenu);
}

// Stock Menu
void stockMenu() // TODO
{
    //show stock, give an option to add or remove and cancel
}