#pragma once //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "utils.h"

void pause();
bool validateMenuInput(const string &input, int &opt);
void limh();
void clearConsole();
void salesMenu();
void productsMenu();
void stockMenu(vector<Stock> &stockList);
void editStockMenu(vector<Stock> &stockList);
void searchEditMenu(vector<Stock> &stockList);

using namespace std;
void pause() // pause the console
{

    cout << "Press enter to continue...";
    cin.ignore();
}

void limh() // horizontal line
{
    cout << "----------------------------------------" << endl;
}

void clearConsole() // clear the console
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
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
            cout << "Sales Menu" << endl;
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
            cout << "Stock Menu" << endl;
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

            cout << "Stock Editing Menu" << endl;
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
        cout << "Stock Search Menu" << endl;
        limh();
        cout << "Please enter a product name to search in stock:" << endl;
        cout << "Name: ";
        getline(cin, name);

        vector<Stock> items = searchForProduct(stockList, name);
        searchMenu = showSearchResults(items);
    } while (searchMenu);
}