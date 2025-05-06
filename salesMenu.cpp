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
            limh(81);
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
    clearConsole();
    setColor("\033[1,33m");
    cout << "Your cart" << endl;
    setColor("\033[0m");

    limh(81);
    setColor("\033[1;36m");
    cout << setw(2) << "ID" << " | "
         << setw(22) << left << "Product Name" << " | "
         << setw(8) << right << "Quantity" << " | "
         << setw(10) << right << "Sale Value" << " eur |"
         << setw(8) << right << "Tax Rate" << "% |"
         << setw(11) << right << "Sale w/ Tax" << " eur |"
         << endl;
    setColor("\033[0m");
    limh(81);

    for (const CartItem &cartItem : cart)
    {
        cout << cartItem.toDisplay() << endl;
    }

    limh(81);
}

void removeProductCart(vector<CartItem> &cart)
{
    int id = getValidatedInt("Insert product ID to remove: ");

    for (int i = 0; i < cart.size(); i++)
    {
        if (cart[i].getStockId() == id)
        {
            cart.erase(cart.begin() + i);
            cout << "Product removed from cart." << endl;
            pause();
            break;
        }
    }
}

void clearCart(vector<CartItem> &cart)
{
    cart.clear();
    cout << "Cart cleared." << endl;
}

void changeProductCart(vector<CartItem> &cart, vector<Stock> &stockList)
{
    int id = getValidatedInt("Insert product ID to change: ");
    int quantity = getValidatedInt("Insert new quantity: ");
    if (quantity > stockList[id].getQuantity())
    {
        cout << "Not enough stock." << endl;
        cout << "Brother we only have " << stockList[id].getQuantity() << " in stock." << endl;

        cout << "Do you want to buy " << stockList[id].getQuantity() << " instead? (y/n): ";
        string input;
        cin >> input;
        if (stringToLower(input) == "y")
            quantity = stockList[id].getQuantity();
        else
            return;
    }
    for (int i = 0; i < cart.size(); i++)
    {
        if (cart[i].getStockId() == id)
        {
            cart[i].setQuantity(quantity);
            cout << "Product quantity changed." << endl;
            pause();
            break;
        }
        else
            cout << "Product not found in cart." << endl;
    }
}