#include "menu.h"

using namespace std;

void mainMenu(vector<Stock> &stockList)
{
    // main loop
    // vars
    bool run = true;
    int opt;
    string input;

    do
    {
        do
        {
            clearConsole();
            setColor("\033[0;36m");
            cout << "Shop menu" << endl;
            setColor("\033[0m");
            limh();
            cout << "1. Shop Sales" << endl;
            limh();
            cout << "2. Shop Stock" << endl;
            limh();
            cout << "3. Exit" << endl;
            limh();
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            // show products, give an option to buy and checkout or cancel
            salesMenu();
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

// Sales Menu
void salesMenu()
{
    bool salesMenu = true;
    string input;
    int salesOpt;
    do
    {
        do
        {
            clearConsole();
            setColor("\033[0;36m");
            cout << "Sales Menu" << endl;
            setColor("\033[0m");
            limh();
            cout << "1. Show Products" << endl;
            limh();
            cout << "2. Go Back" << endl;
            limh();
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, salesOpt));

        switch (salesOpt)
        {
        case 1:
            cout << "Products" << endl;
            limh();
            // show products
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
void productsMenu() // TODO
{
    bool productsMenu = true;
    int productsOpt;
    do
    {
        clearConsole();

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

// Stock Menu
// show stock, give an option to add or remove and cancel
void stockMenu(vector<Stock> &stockList) // TODO
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
            limh();
            cout << "1. Show Stock" << endl;
            limh();
            cout << "2. Edit Stock" << endl;
            limh();
            cout << "3. Go Back" << endl;
            limh();
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, productsOpt));

        switch (productsOpt)
        {
        case 1:
            printStock();
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
            limh();
            cout << "1. Search Stock" << endl;
            limh();
            cout << "2. Add purchase to Stock" << endl;
            limh();
            cout << "3. Change purchase from Stock" << endl;
            limh();
            cout << "4. Remove purchase from Stock" << endl;
            limh();
            cout << "5. Go Back" << endl;
            limh();
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
            cout << "Change purchase from Stock functionality not implemented yet." << endl;
            pause();
            break;
        case 4:
            cout << "Remove purchase from Stock functionality not implemented yet." << endl;
            pause();
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
    bool searchMenu;
    do
    {
        string name;

        clearConsole();
        setColor("\033[0;36m");
        cout << "Stock Search Menu" << endl;
        setColor("\033[0m");
        limh();
        cout << "Please enter a product name to search in stock:" << endl;
        cout << "Name: ";
        getline(cin, name);

        vector<Stock> items = searchForProduct(stockList, name);
        searchMenu = showSearchResults(items);
    } while (searchMenu);
}
