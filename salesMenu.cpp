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
            limh(81);
            cout << "2. Change product in cart" << endl;
            limh(81);
            cout << "3. Remove product from cart" << endl;
            limh(81);
            cout << "4. Checkout" << endl;
            limh(81);
            cout << "5. Clear cart" << endl;
            limh(81);
            if (menuState == 0)
                cout << "6. View Cart" << endl;
            if (menuState == 1)
                cout << "6. View Products" << endl;
            limh;
            cout << "0. Go back" << endl;
            cout << "Option: ";

            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            addProductCart(stockList, cart, menuState);
            break;
        case 2:
            changeProductCart(cart, stockList);
            break;
        case 3:
            removeProductCart(cart);
            break;
        case 4:
            checkout(stockList, cart);
            break;
        case 5:
            clearCart(cart);
            break;
        case 6:
            menuState = !menuState; // flips menuState
            break;

        case 0:
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
        // prints visible menu
        /********************************************************************** */

        clearConsole();
        if (menuState == false)
            printStock(stockList, "Products Menu:\n");
        else
            printCart(stockList, cart);

        int id = getValidatedInt("Insert product ID to add to cart: ");

        /*********************************************************************** */

        // checks initial quantity in stock and its existence
        Stock *item = nullptr;
        if (!findPurchaseFromStock(stockList, item, id) || item == nullptr)
        {

            cout << endl
                 << "Try another ID" << endl;
            pause();
            continue;
        }
        if (item->getQuantity() == 0)
        {
            cout << endl
                 << "0 Stock Brotha ";
            pause();
            continue;
        }
        /*********************************************************************** */
        /*verify item quantity is valid*/
        // needs cycle to ensure cartitem is created, or function is exited
        int quantity = getValidatedInt("How many do you want good sir?: ");
        string input;
        CartItem *bagged_item = findItemCart(cart, item);
        if (bagged_item != nullptr) // verify item existence in cart
        {
            // checking if bagged item quantity matches stock item quantity, if so, refuse to add
            if (item->getQuantity() == bagged_item->getQuantity())
            {
                cout << endl
                     << "0 Stock Brotha" // needs to match earlier cout for immersion efforts
                     << "Try another ID" << endl;
                pause();
                continue;
            }
            // checking if bagged item quantity + input quantity doesn't exceed quantity in stock
            if (item->getQuantity() >= quantity + bagged_item->getQuantity())
            {
                bagged_item->setQuantity(bagged_item->getQuantity() + quantity); // add the input quantity to existing quantity
            }
            else // quantity exceeds, ask user if it should add all remaining quantity anyway
            {
                cout << "Quantity asked exceeds quantity in stock."
                     << endl
                     << "Do you wish to buy all " << item->getQuantity() << " existing items instead? (y/n):";

                getline(cin, input);
                if (stringToLower(input) == "y")
                {
                    bagged_item->setQuantity(item->getQuantity()); // if confirmed will add all existing stock items to cart
                }
            }
        }
        else // bagged item was not found (nullptr) and needs to be created
        {
            // checks again if input quantity doesn't exceed stock quantity
            if (item->getQuantity() >= quantity)
            {
                CartItem newItemCart(*item, quantity); // create the new bagged item
                cart.push_back(newItemCart);           // add the new bagged item the vector cart
            }
            else // if exceeds
            {
                cout << "Quantity asked exceeds quantity in stock."
                     << endl
                     << "Do you wish to buy all " << item->getQuantity() << " existing items instead? (y/n):";

                getline(cin, input);
                if (stringToLower(input) == "y")
                {
                    CartItem newItemCart(*item, item->getQuantity()); // create the new bagged item
                    cart.push_back(newItemCart);                      // add the new bagged item the vector cart
                }
            }
        }

        //
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
    id = id - 1; // fixes index beeing off by one
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

void checkout(vector<Stock> &stockList, vector<CartItem> &cart) // Very fucked initial version
{
    string input;
    if (cart.size() == 0)
    {
        cout << "Cart is empty." << endl;
        pause();
        return;
    }
    cout << "Continue? (y/n): ";
    getline(cin, input);
    if (stringToLower(input) == "y")
    {
        clearConsole();
        cout << "Your cart:" << endl;
        printCart(stockList, cart);
        double total = 0;
        for (const CartItem &cartItem : cart)
        {
            total += cartItem.getTotalItemSellValue();
        }
        cout << "Total: " << total << " eur" << endl;
        pause(); // give option to cancel around here
        double paymentAmount = getValidatedDouble("Insert payment amount: ");
        do
        {
            if (paymentAmount < total)
            {
                cout << "Not enough money." << endl;
                cout << "Do you want to try again? (y/n): ";
                string input;
                cin >> input;
                if (stringToLower(input) == "y")
                    paymentAmount = getValidatedDouble("Insert payment amount: ");
                else
                    return;
            }
        } while (paymentAmount < total);
        Receipt receipt(cart, paymentAmount);
        cout << receipt.toDisplay() << endl;
        pause();
    }
    else
        return;
}