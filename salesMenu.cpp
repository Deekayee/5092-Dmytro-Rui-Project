#include "salesMenu.h"

using namespace std;

// Sales Menu
void salesMenu(vector<Stock> &stockList, vector<CartItem> &cart)
{
    bool salesMenu = false;
    // salesMenu:
    //  0-Shows Products
    //  1-Shows Cart
    string input;
    int opt;
    do
    {
        do
        {
            if (salesMenu == false)
                printStock(stockList, "Products Menu:\n");
            if (salesMenu == true)
                printCart(stockList, cart);
            limh();

            cout << "Options:" << endl
                 << "1. Add product to cart" << endl;
            if (salesMenu == 1)
                cout << "2. View Cart" << endl;
            if (salesMenu == 2)
                cout << "2. View Products" << endl;
            cout << "3. Go back" << endl;
            cout << "Option: ";

            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            addProductCart(stockList, cart, salesMenu);
            break;
        case 2:
            salesMenu++;
            break;
        case 3:
            return;
            break;

        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }

    } while (true);
}

// Adds items to Cart similar to addPurchaseToStock()
void addProductCart(vector<Stock> &stockList, vector<CartItem> &cart, bool salesMenu)
{
    if (salesMenu == false)
        printStock(stockList, "Products Menu:\n");
    if (salesMenu == true)
        printCart(stockList, cart);
    /*TO DO*/

    return;
}

// Prints items in cart similar to printStock()
void printCart(vector<Stock> &stockList, vector<CartItem> &cart) // TODO
{
    /*TO DO*/

    return;
}