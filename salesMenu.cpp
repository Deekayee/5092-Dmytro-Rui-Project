#include "salesMenu.h"


using namespace std;


// Sales Menu
void salesMenu(vector <Stock> &stockList, vector <CartItem> &cart)
{
    bool salesMenu = true;
    string input;
    int salesOpt;
    do
    {
        do
        {
            
            
            limh();
            cout << "Options:" << endl
                 << "1. Add product to cart" << endl
                 << "2. View Cart" << endl;
            cout << "Option: ";

            getline(cin, input);
        } while (!validateMenuInput(input, salesOpt));

        switch (salesOpt)
        {
        case 1:
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
int productsMenu() // TODO
{
    bool productsMenu = true;
    int productsOpt;
    do
    {

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