#include "salesMenu.h"

using namespace std;

// Sales Menu
void salesMenu(vector<Stock> &stockList, vector<CartItem> &cart)
{
    bool menuState = false;
    string input;
    int opt;
    do
    {
        do
        {
            clearConsole();

            // Depending on the state of the menu
            // will print either the products in stock or in cart
            //   menuState:
            //   0 -> Shows Products (default)
            //   1 -> Shows Cart
            if (menuState == false)
            // needs to print price for client, meaning, profit margin + maybe with tax
                printStock(stockList, "Products Menu:\n");
            if (menuState == true)
                printCart(stockList, cart);

            cout << "Options:" << endl;
            limh();
            cout << "1. Add product to cart" << endl;
            limh;
            if (menuState == 0)
                cout << "2. View Cart" << endl;
            if (menuState == 1)
                cout << "2. View Products" << endl;
                limh;
            cout << "3. Go back" << endl;
            cout << "Option: ";

            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            addProductCart(stockList, cart, menuState);
            break;
        case 2:
            menuState = !menuState; // flips menuState
            break;
        case 3:
            return;

        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }

    } while (true);
}

// Adds items to Cart similar to addPurchaseToStock()
void addProductCart(vector<Stock> &stockList, vector<CartItem> &cart, bool menuState)
{
    clearConsole();
    if (menuState == false)
        printStock(stockList, "Products Menu:\n");
    if (menuState == true)
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