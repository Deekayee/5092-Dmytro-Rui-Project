#include "stockMenu.h"

using namespace std;

void mainMenu(vector<Stock> &stockList)
{
    // main loop
    // vars
    bool run = true;
    int opt;
    string input;
    vector <CartItem> cart;
    do
    {
        do
        {
            clearConsole();
            setColor("\033[0;36m");
            cout << "Shop menu" << endl;
            setColor("\033[0m");
            limh(81);
            cout << "1. Shop Sales" << endl;
            limh(81);
            cout << "2. Shop Stock" << endl;
            limh(81);
            cout << "3. Exit" << endl;
            limh(81);
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            // show products, give an option to buy and checkout or cancel
            salesMenu(stockList, cart);
            break;
        case 2:
            // show stock, give an option to add or remove and cancel
            stockMenu(stockList);
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

// Stock Menu
// show stock, give an option to add or remove and cancel
void stockMenu(vector<Stock> &stockList)
{
    bool stockMenu = true;
    string input;
    int productsOpt;

    do
    {
        do
        {
            clearConsole();
            setColor("\033[0;36m");
            cout << "Stock Menu" << endl;
            setColor("\033[0m");
            limh(81);
            cout << "1. Show Stock" << endl;
            limh(81);
            cout << "2. Edit Stock" << endl;
            limh(81);
            cout << "3. Go Back" << endl;
            limh(81);
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, productsOpt));

        switch (productsOpt)
        {
        case 1:
            printStock(stockList, "Stock\n");
            break;
        case 2:
            editStockMenu(stockList);
            break;

        case 3:
            stockMenu = false;
            break;
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }

    } while (stockMenu);
}

//  In charge of Adding, Changing, Removing and Searching in stock (search is for fun!)
void editStockMenu(vector<Stock> &stockList)
{
    bool editMenu = true;
    string input;
    int opt;
    do
    {
        do
        {
            clearConsole();

            setColor("\033[0;36m");
            cout << "Stock Editing Menu" << endl;
            setColor("\033[0m");
            limh(81);
            cout << "1. Search Stock" << endl;
            limh(81);
            cout << "2. Add purchase to Stock" << endl;
            limh(81);
            cout << "3. Change purchase from Stock" << endl;
            limh(81);
            cout << "4. Remove purchase from Stock" << endl;
            limh(81);
            cout << "5. Go Back" << endl;
            limh(81);
            cout << "Option: ";
            getline(cin, input);

        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            searchEditMenu(stockList);
            break;
        case 2:
            addPurchaseToStock(stockList);
            break;
        case 3:
            // cout << "Change purchase from Stock functionality not implemented yet." << endl;
            // pause();
            changeEditMenu(stockList);
            break;
        case 4:
            // cout << "Remove purchase from Stock functionality not implemented yet." << endl;
            // pause();
            removeEditMenu(stockList);
            break;
        case 5:
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
        string name;

        clearConsole();
        setColor("\033[0;36m");
        cout << "Stock Search Menu" << endl;
        setColor("\033[0m");
        limh(81);
        cout << "Please enter a product name to search in stock:" << endl;
        cout << "Name: ";
        getline(cin, name);

        vector<Stock> items = searchForProduct(stockList, name);
        run = showSearchResults(items);
    } while (run);
}
void changeEditMenu(vector<Stock> &stockList)
{
    vector <int> idColor;   // saves ids for marking when changed
    while (true)
    {
        string prompt;
        int id;
        do
        {
            printStock(stockList, "Change Item Menu", idColor, "\033[0;32m");
            /*clearConsole();
            setColor("\033[1;33m");
            cout << "Changing item from stock:\n";
            setColor("\033[0m");

            limh(81);
            setColor("\033[1;36m");
            cout << "ID | Product Name           | Quantity | Cost eur" << endl;
            setColor("\033[0m");
            limh(81);

            for (const Stock &item : stockList)
            {
                int colorMarker = 0;
                if (item.getQuantity() == 0)
                    colorMarker = 2;
                else
                    for (int i : ids)
                        if (item.getStockId() == i)
                        {
                            colorMarker = 1;
                            break;
                        }

                if (colorMarker == 1)
                    setColor("\033[0;32m"); // greem for recent change
                if (colorMarker == 2)
                    setColor("\033[1;31m"); // red for zero quantity

                cout << item.toDisplay() << endl;

                if (colorMarker != 0)
                    setColor("\033[0m"); // resets color
            }*/

            limh(81);

            cout << "Please enter the ID of the product you wish to change (Enter 0 to return)" << endl;
            cout << "ID: ";
            getline(cin, prompt);

        } while (!validateMenuInput(prompt, id));
        if (id <= 0) // go back in menu
            return;

        Stock *item;
        if (!findPurchaseFromStock(stockList, item, id) || item == nullptr)
        {
            cout << "Item not found in stock" << endl;
            pause();
            continue;
        }
        clearConsole();

        setColor("\033[0;36m");
        cout << "Changing product: " << item->getStockId() << "-" << item->getProductName() << endl;
        setColor("\033[0m");

        cout << "Do you wish to proceed? (y/n):";
        getline(cin, prompt);
        if (prompt != "y")
        {
            continue;
        }
        limh(81);

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

        idColor.push_back(item->getStockId());
        cout << "Do you wish to keep editing items? (y/n): ";
        getline(cin, prompt);
        if (prompt != "y")
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
            printStock(stockList, "Remove Item Menu", idColor, "\033[0;33m");
            /*clearConsole();
            setColor("\033[1;33m");
            cout << "Removing from stock:\n";
            setColor("\033[0m");

            limh(81);
            setColor("\033[1;36m");
            cout << "ID | Product Name           | Quantity | Cost eur" << endl;
            setColor("\033[0m");
            limh(81);

            for (Stock &item : stockList)
            {
                int colorMarker = 0;

                if (item.getQuantity() == 0)
                    colorMarker = 2;

                for (int i : ids)
                    if (item.getStockId() == i)
                    {
                        colorMarker = 1;
                        break;
                    }

                if (colorMarker == 2)
                    setColor("\033[1;31m"); // red for zero quantity
                else if (colorMarker == 1)
                    setColor("\033[0;33m"); // yellow for recent change (with zero quantity)

                cout << item.toDisplay() << endl;

                if (colorMarker != 0)
                    setColor("\033[0m"); // resets color
            }*/

            limh(81);

            cout << "Please enter the ID of the product you wish to remove (Enter 0 to return)" << endl;
            cout << "ID: ";
            getline(cin, prompt);

        } while (!validateMenuInput(prompt, id));
        if (id <= 0) // go back in menu
            return;

        Stock *item;
        if (!findPurchaseFromStock(stockList, item, id) || item == nullptr)
        {
            cout << "Item not found in stock" << endl;
            pause();
            continue;
        }
        clearConsole();

        setColor("\033[0;36m");
        cout << "Removing product: " << item->getStockId() << "-" << item->getProductName() << endl;
        setColor("\033[0m");
        cout << "Do you wish to proceed? (y/n):";
        getline(cin, prompt);
        if (prompt != "y")
        {
            continue;
        }
        limh(81);
        
        Stock newItem;
        newItem.setStockId(item->getStockId());
        newItem.setProductName(item->getProductName());
        newItem.setCostValue(item->getCostValue());
        newItem.setQuantity(0);
        idColor.push_back(item->getStockId());
        changePurchaseFromStock(stockList, item, newItem);

        cout << "Do you wish to keep removing items? (y/n): ";
        getline(cin, prompt);
        if (prompt != "y")
            return;
    }
}