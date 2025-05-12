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
            int limiterType;
            if (menuState == false)
            {
                // needs to print price for client, meaning, profit margin + maybe with tax
                printProducts(shelf);
                limiterType = PRODUCTS_DASH;
            }
            if (menuState == true)
            {
                printCart(cart);
                limiterType = CART_DASH;
            }

            setColor(BLUE);
            cout << "Sales Options:" << endl;
            setColor(RESET);
            limh(limiterType);
            cout << "1. Add product to cart" << endl;
            limh(limiterType);
            cout << "2. Change product in cart" << endl;
            limh(limiterType);
            cout << "3. Remove product from cart" << endl;
            limh(limiterType);
            cout << "4. Checkout" << endl;
            limh(limiterType);
            cout << "5. Clear cart" << endl;
            limh(limiterType);
            if (menuState == 0)
                cout << "6. View Cart" << endl;
            if (menuState == 1)
                cout << "6. View Products" << endl;
            limh(limiterType);
            cout << "0. Go back" << endl;
            limh(limiterType);
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
            checkoutMenu(stockList, shelf, cart);
            break;
        case 5:
            clearCart(cart, &shelf);
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
            printProducts(shelf);
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
                     << endl;

                stringstream ss;
                ss << "Do you wish to buy all " << item->getQuantity() << " existing items instead?";
                if (promptYESOrNo(ss.str()))
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
                     << endl;

                stringstream ss;
                ss << "Do you wish to buy all " << item->getQuantity() << " existing items instead?";
                if (promptYESOrNo(ss.str()))
                {
                    CartItem newItemCart(*item, item->getQuantity()); // create the new bagged item
                    cart.push_back(newItemCart);                      // add the new bagged item the vector cart
                    item->setQuantity(0);
                }
            }
        }

        cout << "Cart Updated!" << endl;

        if (promptyesOrNO())
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
            printProducts(shelf);
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
            item->setQuantity(item->getQuantity() + bagged_item->getQuantity());

            cout << "Product removed from cart." << endl;
            if (!promptyesOrNO("Do you wish to continue removing?"))
            {
                break;
            }
        }
        else
        {
            cout << "Item not found." << endl;
            if (!promptyesOrNO("Do you wish to continue removing?"))
            {
                break;
            }
        }
    }
}

void clearCart(vector<CartItem> &cart, vector<Stock> *shelf)
{
    // *this case represents a canceled sale through the menu
    // here we need to bring back the quantities in the cart back to the shelf
    // before deleting them
    if (shelf != nullptr)
        for (CartItem &bagged_item : cart)
        {
            // update
            Stock *item = findStock(*shelf, bagged_item.getStockId());
            item->setQuantity(bagged_item.getQuantity() + item->getQuantity());
        }
    // *otherwise, if shelf isnt specified, it means checkout is happening, so
    // the shelf already owns the correct quantities and is ready to update our
    // stockList
    cart.clear();
    cout << "Cart cleared." << endl;
}

void changeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
    while (true)
    {

        clearConsole();
        if (menuState == false)
            printProducts(shelf);
        else
            printCart(cart);

        int id = getValidatedInt("Insert product ID in cart to change: ");

        CartItem *bagged_item = findItemCart(cart, id);
        if (bagged_item) // if item exists in cart
        {

            Stock *item = findStock(shelf, id);

            // removed bc of redundancy
            // if (!item) // but if item was not found in our shelf
            // {
            //     cout << endl
            //          << "Something weird happened, item present in cart but not in stock???" << endl;
            //     return;
            // }

            int item_quantity = item->getQuantity();
            int bagged_quantity = bagged_item->getQuantity();
            int quantity = getValidatedInt("Insert new quantity: ");
            quantity = quantity - bagged_item->getQuantity(); // will be the added/removed quantity from either cart or shelf

            if (quantity > item->getQuantity())
            {
                cout << "Not enough stock."
                     << endl;

                stringstream ss;
                ss << "Do you wish to buy all " << item->getQuantity() << " remaining items instead? ";
                if (promptYESOrNo(ss.str()))
                {
                    bagged_item->setQuantity(item_quantity + bagged_quantity);
                    item->setQuantity(0);
                }
                else
                    return;
            }
            else
            {
                bagged_item->setQuantity(quantity + bagged_quantity);
                item->setQuantity(item_quantity - quantity);
            }
            cout << "Product quantity changed." << endl;
            if (!promptyesOrNO("Do you want to continue adjusting? "))
                return;
        }
        else // if it doesn't exist in cart, refuse to update
        {
            string input;
            cout << "Product not found in cart. Please select a valid ID" << endl;
            if (!promptyesOrNO("Do you want to continue adjusting? "))
                return;
        }
    }
}

void checkoutMenu(vector<Stock> &stockList, vector<Stock> &shelf, vector<CartItem> &cart) // Very fucked initial version
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
    for (CartItem &cartItem : cart)
    {
        total += cartItem.getTotalItemSellValue();
    }
    cout << "Total: " << total << " eur" << endl;

    if (promptYESOrNo("Do you wish to confirm?"))
    {
        double paymentAmount = getValidatedDouble("Insert payment amount: ");
        do
        {
            if (paymentAmount < total)
            {
                cout << "Nice joke, that's not enough." << endl; // removed the other jokes sorry but i like this one
                if (promptYESOrNo("Do you want to try again?"))
                    paymentAmount = getValidatedDouble("Insert payment amount: ");
                else
                    return;
            }
        } while (paymentAmount < total);

        clearConsole();

        gambling(cart);
        Receipt receipt(cart, paymentAmount);

        cout << receipt.toDisplay();
        updateStockFromShelf(stockList, shelf);

        clearCart(cart);
        pause();
    }
    else
        return;
}

void gambling(vector<CartItem> &sale, int chance)
{
    srand(time(0));
    int badLuck = (rand() % 101); // badluck goes from 0 to 100

    if (badLuck < chance) // if the "bad luck" is less than the chance, win
    {
        vector<CartItem> roster = sale;

        srand(time(0));                           // reinitializing seed
        int sortedIndex = rand() % roster.size(); // randomizing index

        CartItem jackpot = roster.at(sortedIndex);
        cout << "You won a free " << jackpot.getProductName() << "!" << endl;
        jackpot.setQuantity(1); // client only gets one, >:(

        int resetPrice = 0 - jackpot.getSaleWithoutTax(); // price is negative to subtract total
        jackpot.setSaleWithoutTax(resetPrice);

        sale.push_back(jackpot); // item gets added at end of receipt for display
    }
}

// void gambling(Receipt &sale, int chance)
// {
//     srand(time(0));
//     int badLuck = (rand() % 101); // badluck goes from 0 to 100

//     if (badLuck < chance)         // if the "bad luck" is less than the chance, win
//     {
//         vector<CartItem> roster = sale.getItems();

//         srand(time(0));                           // reinitializing seed
//         int sortedIndex = rand() % roster.size(); // randomizing index

//         CartItem jackpot = roster.at(sortedIndex);
//         cout << "You won a free " << jackpot.getProductName() << "!" << endl;
//         jackpot.setQuantity(1); // client only gets one, >:(

//         int resetPrice = 0 - jackpot.getSaleWithoutTax(); //price is negative to subtract total
//         jackpot.setSaleWithoutTax(resetPrice);

//         sale.getItems().push_back(jackpot); //item gets added at end of receipt for display
//     }
// }

// bool registerLogin()
// {
//     clearConsole();
//     setColor(YELLOW);
//     cout << "Registering Client";
//     setColor(RESET);
//     limh();

//     fstream credentials("loginInfo.csv", ios::app);

//     cout << "Please insert name: ";
//     string name;
//     getline(cin, name);
// }
// bool login()
// {

// }