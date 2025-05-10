#include "salesMenu.h"

using namespace std;

// Sales Menu
void salesMenu(vector<Stock> &stockList, vector<Stock> &shelf, vector<CartItem> &cart)
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
            //   false -> Shows Products (default)
            //   true -> Shows Cart
            if (menuState == false)
                // needs to print price for client, meaning, profit margin + maybe with tax
                printStock(shelf, "Products Menu:\n");
            if (menuState == true)
                printCart(cart);

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
            limh(81);
            cout << "0. Go back" << endl;
            limh(81);
            cout << "Option: ";

            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            addProductCart(shelf, cart, menuState);
            break;
        case 2:
            changeProductCart(shelf, cart, menuState);
            break;
        case 3:
            removeProductCart(shelf, cart, menuState);
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

CartItem *findItemCart(vector<CartItem> &cart, int id, int *index)
{
    for (int i = 0; i < cart.size(); i++)
    {
        if (cart.at(i).getStockId() == id)
        {
            if (index != nullptr)
                *index = i;
            return &cart.at(i); // finds and returns reference to item
        }
    }
    return nullptr;
}

// Prints items in cart similar to printStock()
void printCart(vector<CartItem> &cart) // TODO
{
    /*TO DO*/
    clearConsole();
    setColor(YELLOW);
    cout << "Your cart" << endl;
    setColor(RESET);

    limh(81);
    setColor(CYAN);
    cout << setw(2) << "ID" << " | "
         << setw(22) << left << "Product Name" << " | "
         << setw(8) << right << "Quantity" << " | "
         << setw(10) << right << "Sale Value" << " eur |"
         << setw(8) << right << "Tax Rate" << "% |"
         << setw(11) << right << "Sale w/ Tax" << " eur |"
         << endl;
    setColor(RESET);
    limh(81);

    for (const CartItem &cartItem : cart)
    {
        cout << cartItem.toDisplay() << endl;
    }

    limh(81);
}

// Adds items to Cart similar to addPurchaseToStock()
// adding items works, it checks for a valid quantity and never adds more than what stock can take, except for that it doesnt update stock yet
// to dos:
//  -update stock (but only on checkout, a later task)
//  -check if stock is empty before adding the item and display appropriate output
//  -a checkout option
void addProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
    /*TO DO*/
    while (true)
    {

        // prints visible menu

        clearConsole();
        if (menuState == false)
            printStock(shelf, "Products Menu:\n");
        else
            printCart(cart);

        int id = getValidatedInt("Insert product ID to add to cart: ");

        // checks initial quantity in stock and its existence
        Stock *item = findStock(shelf, id);
        if (item == nullptr)
        {

            cout << endl
                 << "Try another ID" << endl;
            pause();
            continue;
        }
        if (item->getQuantity() == 0)
        {
            cout << endl
                 << "Out of Stock. " << endl;
            pause();
            continue;
        }

        /*verify item quantity is valid*/
        // needs cycle to ensure cartitem is created, or function is exited
        int quantity = getValidatedInt("How many do you want good sir?: ");
        string input;

        CartItem *bagged_item = findItemCart(cart, item->getStockId());
        if (bagged_item != nullptr) // item exists in cart
        {

            // checking if input quantity doesn't exceed quantity in shelf
            if (item->getQuantity() >= quantity)
            {
                bagged_item->setQuantity(bagged_item->getQuantity() + quantity); // add the input quantity to existing quantity
                item->setQuantity(item->getQuantity() - quantity);               // remove the input quantity from shelf
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
                    item->setQuantity(0);                          // as we add to cart, we remove from shelf
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
                item->setQuantity(item->getQuantity() - quantity);
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
                    item->setQuantity(0);
                }
            }
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

void removeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
    while (true)
    {
        clearConsole();

        if (menuState == false)
            printStock(shelf, "Products Menu:\n");
        else
            printCart(cart);
        int id = getValidatedInt("Insert product ID to remove: ");

        int index;
        CartItem *bagged_item = findItemCart(cart, id, &index);
        Stock *item = findStock(shelf, id);

        string input;
        if (bagged_item != nullptr)
        {
            cart.erase(cart.begin() + index);
            item->setQuantity(item->getQuantity()+bagged_item->getQuantity());

            cout << "Product removed from cart." << endl
                 << "Do you wish to continue removing ? (y/n): ";

            getline(cin, input);
            if (stringToLower(input) != "y" && !input.empty())
            {
                break;
            }
        }
        else
        {
            cout << "Item not found." << endl
                 << "Do you wish to continue removing? (y/n): "; // assumes 'y' as default

            getline(cin, input);
            if (stringToLower(input) != "y" && !input.empty())
            {
                break;
            }
        }
    }
}

void clearCart(vector<CartItem> &cart)
{
    cart.clear();
    cout << "Cart cleared." << endl;
}

void changeProductCart(const vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
    clearConsole();
    if (menuState == false)
        printStock(shelf, "Products Menu:\n");
    else
        printCart(cart);

    //
    int id = getValidatedInt("Insert product ID to change: ");
    int quantity = getValidatedInt("Insert new quantity: ");
    const Stock *stockPtr = nullptr; // blank pointer to be used later
    for (const auto &stock : shelf)
    {
        if (stock.getStockId() == id)
        {
            stockPtr = &stock; // sets stockPtr to address of wanted stock thingy
            break;
        }
    }
    if (!stockPtr)
    {
        cout << "Product not found in stock." << endl;
        pause();
        return;
    }
    if (quantity > stockPtr->getQuantity())
    {
        cout << "Not enough stock." << endl;
        cout << "Brother we only have " << stockPtr->getQuantity() << " in stock." << endl;

        cout << "Do you want to buy " << stockPtr->getQuantity() << " instead? (y/n): ";
        string input;
        getline(cin, input);
        if (stringToLower(input) == "y")
            quantity = stockPtr->getQuantity();
        else
            return;
    }
    bool found = false;
    for (CartItem &cartItem : cart)
    {
        if (cartItem.getStockId() == id)
        {
            cartItem.setQuantity(quantity);
            cout << "Product quantity changed." << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Product not found in cart." << endl;
    pause();
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
    clearConsole();
    cout << "Your cart:" << endl;
    printCart(cart);
    double total = 0;
    for (const CartItem &cartItem : cart)
    {
        total += cartItem.getTotalItemSellValue();
    }
    cout << "Total: " << total << " eur" << endl;
    // cout << "Continue? (y/n): ";
    cout << "Continue? (" << underline << "Y" << RESET << "/n): ";
    getline(cin, input);
    if (stringToLower(input) == "y" || input.empty())
    {
        double paymentAmount = getValidatedDouble("Insert payment amount: ");
        do
        {
            if (paymentAmount < total)
            {
                cout << "Nice joke, that's not enough." << endl;
                cout << "Do you want to try again? (y/n): ";
                getline(cin, input);
                if (stringToLower(input) == "y")
                    paymentAmount = getValidatedDouble("Insert payment amount: ");
                else
                    return;
            }
        } while (paymentAmount < total);
        Receipt receipt(cart, paymentAmount);
        clearConsole();
        cout << receipt.toDisplay();
        for (const CartItem &cartItem : cart)
        {
            Stock *stockPtr = findStock(stockList, cartItem.getStockId());
            if (stockPtr)
            {
                int newQuantity = stockPtr->getQuantity() - cartItem.getQuantity();
                changeQuantityFromStock(stockList, cartItem.getStockId(), newQuantity);
            }
        }

        cart.clear();
        pause();
    }
    else
        return;
}