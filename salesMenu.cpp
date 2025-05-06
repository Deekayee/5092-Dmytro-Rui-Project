#include "salesMenu.h"


using namespace std;


// Sales Menu
void salesMenu()
{
    bool salesMenu = true;
    string input;
    int salesOpt;
    do
    {
        do
        {
            clearConsole();
            setColor("\033[0;36m");
            cout << "Sales Menu" << endl;
            setColor("\033[0m");
            limh();
            cout << "1. Show Products" << endl;
            limh();
            cout << "2. Go Back" << endl;
            limh();
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, salesOpt));

        switch (salesOpt)
        {
        case 1:
            cout << "Products" << endl;
            limh();
            // show products
            productsMenu();
            break;
        case 2:
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
        cout << "Products" << endl;
        limh();

        /*Show products here*/

        cin >> productsOpt;
        cout << endl
             << "Press 0 to go cancel" << endl; // placeholder
        cin.ignore();

        if (productsOpt == 0)
            productsMenu = false;

    } while (productsMenu);
}