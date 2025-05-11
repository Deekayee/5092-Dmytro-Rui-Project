#include "stockMenu.h"

using namespace std;

void mainMenu(vector<Stock> &stockList)
{
    // main loop
    // vars
    bool run = true;
    int opt;
    string input;
    vector<CartItem> cart;
    vector<Stock> shelf;
    // adding copy of stockList to shelf
    // this will display items to user in specified order:
    do
    {   
        shelfInit(stockList, cart, shelf);
        do
        {
            clearConsole();
            setColor(Cyan);
            cout << "Shop menu" << endl;
            setColor(RESET);
            limh(STOCK_DASH);
            cout << "1. Shop Sales" << endl;
            limh(STOCK_DASH);
            cout << "2. Shop Stock" << endl;
            limh(STOCK_DASH);
            cout << "3. Exit" << endl;
            limh(STOCK_DASH);
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            // show products, give an option to buy and checkout or cancel
            salesMenu(stockList, shelf, cart);
            break;
        case 2:
            // show stock, give an option to add or remove and cancel, among some other bonus features
            // bar access to stock if a sale is in process, in order to prevent mismanagement of stock and shelf items
            if (!cart.empty())
            {
                cout << "You have products in cart! Clear the cart or finish checking out to proceed" << endl
                     << "Unable to access stock menu" << endl;
                pause();
                break;
            }
            editStockMenu(stockList);
            break;
        case 3:
            // exit
            clearConsole();
            run = false;
            break;
        default:
            // user is a bit slow, what can we do
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }
    } while (run);
}

//  In charge of Adding, Changing, Removing and Searching in stock (search is for fun!)
void editStockMenu(vector<Stock> &stockList)
{
    bool editMenu = true;
    string input;
    int opt;
    do
    {
        clearConsole();
        printStock(stockList, "Stock View");

        setColor(Cyan);
        cout << "Stock Editing Menu" << endl;
        setColor(RESET);
        limh(STOCK_DASH);
        cout << "1. Search Stock" << endl;
        limh(STOCK_DASH);
        cout << "2. Add purchase to Stock" << endl;
        limh(STOCK_DASH);
        cout << "3. Change purchase from Stock" << endl;
        limh(STOCK_DASH);
        cout << "4. Remove purchase from Stock" << endl;
        limh(STOCK_DASH);
        cout << "0. Go Back" << endl;
        limh(STOCK_DASH);
        cout << "Option: ";
        getline(cin, input);
        if (!validateMenuInput(input, opt))
            continue;

        switch (opt)
        {
        case 1:
            searchEditMenu(stockList);
            break;
        case 2:
            addPurchaseToStock(stockList);
            break;
        case 3:
            changeEditMenu(stockList);
            break;
        case 4:
            removeEditMenu(stockList);
            break;
        case 0:
            editMenu = false;
            break;
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }

    } while (editMenu);
}
void searchEditMenu(vector<Stock> &stockList)
{
    bool run;
    do
    {
        clearConsole();
        printStock(stockList, "Stock View");

        string name;
        setColor(Cyan);
        cout << "Stock Search Menu" << endl;
        setColor(RESET);
        limh(STOCK_DASH);
        cout << "Please enter a product name to search in stock:" << endl;
        cout << "Name: ";
        getline(cin, name);

        vector<Stock> items = searchForProduct(stockList, name);
        run = showSearchResults(items);
    } while (run);
}
void changeEditMenu(vector<Stock> &stockList)
{
    vector<int> idColor; // saves ids for marking when changed
    while (true)
    {
        clearConsole();
        printStock(stockList, "Change Item Menu", &idColor, Green);

        string prompt;
        int id;
        cout << "Please enter the ID of the product you wish to change (Enter 0 to return)" << endl;
        cout << "ID: ";
        getline(cin, prompt);

        if (!validateMenuInput(prompt, id))
            continue;

        if (id <= 0) // go back in menu
            return;

        Stock *item = findStock(stockList, id);
        if (item == nullptr)
        {
            cout << "Item not found in stock" << endl;
            pause();
            continue;
        }
        clearConsole();
        printStock(stockList, "Stock View");

        setColor(Cyan);
        cout << "Changing product: " << item->getStockId() << "-" << item->getProductName() << endl;
        setColor(RESET);
        limh();

        if (!promptYESOrNo("Do you wish to proceed?"))
        {
            continue;
        }
        limh(STOCK_DASH);

        stringstream itemString;
        itemString << item->getStockId() << ",";
        cout << "Enter new product data" << endl;
        cout << "Product name: ";
        getline(cin, prompt);
        itemString << prompt << ",";
        itemString << getValidatedInt("Quantity: ") << ",";
        itemString << getValidatedDouble("Cost: ");

        Stock newItem;
        newItem.fromString(itemString.str());
        changePurchaseFromStock(stockList, item, newItem);
        cout << "Stock Updated!" << endl;

        idColor.push_back(item->getStockId());

        if (!promptyesOrNO("Do you wish to keep editing items?"))
            return;
    }
}
void removeEditMenu(vector<Stock> &stockList)
{
    vector<int> idColor; // saves ids for marking when changed
    while (true)
    {
        string prompt;
        int id;
        do
        {
            printStock(stockList, "Remove Item Menu", &idColor, Yellow);

            limh(STOCK_DASH);

            cout << "Please enter the ID of the product you wish to remove (Enter 0 to return)" << endl;
            cout << "ID: ";
            getline(cin, prompt);

        } while (!validateMenuInput(prompt, id));
        if (id <= 0) // go back in menu
            return;

        Stock *item = findStock(stockList, id);
        if (item == nullptr)
        {
            cout << "Item not found in stock" << endl;
            pause();
            continue;
        }

        setColor(Cyan);
        cout << "Removing product: " << item->getStockId() << "-" << item->getProductName() << endl;
        setColor(RESET);
        if (!promptYESOrNo())
        {
            continue;
        }
        limh(STOCK_DASH);

        removePurchaseFromStock(stockList, item);
        cout << "Stock Updated!" << endl;

        if (!promptyesOrNO("Do you wish to keep removing items?"))
            return;
    }
}

// Stock Menu
// show stock, give an option to add or remove and cancel
// void stockMenu(vector<Stock> &stockList)
// {
//     bool stockMenu = true;
//     string input;
//     int productsOpt;

//     do
//     {
//         // added printstock here
//         clearConsole();
//         printStock(stockList, "Stock View");

//         setColor(Cyan);
//         cout << "Stock Menu" << endl;
//         setColor(RESET);
//         limh(MENU_DASH);
//         cout << "1. Show Stock" << endl;
//         limh(MENU_DASH);
//         cout << "2. Edit Stock" << endl;
//         limh(MENU_DASH);
//         cout << "3. Go Back" << endl;
//         limh(MENU_DASH);
//         cout << "Option: ";
//         getline(cin, input);
//         // changing from cycle to if statement
//         if (!validateMenuInput(input, productsOpt))
//             continue; // if menu option doesnt check out, will repeat our functio, needed to more easily print stock

//         switch (productsOpt)
//         {
//         case 1:
//             printStock(stockList, "Stock\n");
//             pause();
//             break;
//         case 2:
//             editStockMenu(stockList);
//             break;

//         case 3:
//             stockMenu = false;
//             break;
//         default:
//             cout << "Invalid input, try again." << endl;
//             pause();
//             break;
//         }

//     } while (stockMenu);
// }