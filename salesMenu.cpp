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
// adding items works, it checks for a valid quantity and never adds more than what stock can take, except for that it doesnt update stock yet
// to dos:
//  -update stock (but only on checkout, a later task)
//  -check if stock is empty before adding the item and display appropriate output
//  -a checkout option
void addProductCart(vector<Stock> &stockList, vector<CartItem> &cart, bool menuState)
{
    /*TO DO*/
    while (true)
    {
        clearConsole();
        if (menuState == false)
            printStock(stockList, "Products Menu:\n");
        else
            printCart(stockList, cart);

        string input;
        int id;

        id = getValidatedInt("Add product by ID");

        Stock *item = nullptr;
        if (!findPurchaseFromStock(stockList, item, id) || item == nullptr)
        {
            cout << "Try another ID" << endl;
            continue;
        }

        int quantity = getValidatedInt("How many do you want good sir?: ");

        /*verify item quantity is valid*/
        // needs cycle to ensure cartitem is created, or function is exited

        CartItem *bagged_item = findItemCart(cart, item);
        if (bagged_item != nullptr) // verify item existence in cart
        {
            // missing check condition for when bagged item already corresponds in quantity to stock item
            if (item->getQuantity() >= quantity + bagged_item->getQuantity()) // verify quantity in stock before any operation
            {
                bagged_item->setQuantity(bagged_item->getQuantity() + quantity); // add the input quantity to existing quantity
            }
            else // quantity exceeds
            {
                cout << "Quantity asked exceeds quantity in stock."
                     << endl
                     << "Do you wish to buy all " << item->getQuantity() << " items? (y/n):";
                getline(cin, input);
                if (input == "y")
                {
                    bagged_item->setQuantity(item->getQuantity());
                }
            }
        }
        else // bagged item was not found (nullptr) and needs to be created
        {
            CartItem newItemCart(*item, quantity);
            cart.push_back(newItemCart); // add the produced cartIteminto the vector cart
        }
        cout << "Cart Updated!" << endl;
        cout << "Continue? (y/n): ";
        getline(cin, input);
        if (input == "y")
            continue;
        else
            return;
    }
}
CartItem *findItemCart(vector<CartItem> &cart, Stock *item)
{
    for (CartItem &checker : cart)
    {
        if (checker.getStockId() == item->getStockId())
            return &checker;
    }
    return nullptr;
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