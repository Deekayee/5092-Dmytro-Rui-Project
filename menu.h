#pragma once    //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "utils.h"

using namespace std;
void pause() // pause the console
{
    cout << "Press enter to continue...";
    cin.ignore();
}

bool validateMenuInput(const string &input, int &opt)
{
    // Check if the string is entirely digits
    for (char ch : input)
    {
        if (!isdigit(ch))
        {
            cout << "Please enter a number" << endl;
            pause();
            return false;
        }
    }

    // catch exceptions
    try
    {
        opt = stoi(input);
    }
    catch (const std::out_of_range &)
    {
        cout << "Number is too large. Please enter a smaller number." << endl;
        pause();
        return false;
    }
    catch (const std::invalid_argument &)
    {
        cout << "Invalid input. Please enter numbers only." << endl;
        pause();
        return false;
    }
    return true;
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
            printStockFile();
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
        limh();

        cin >> productsOpt;
        cin.ignore();

    } while (productsMenu);
}

// Stock Menu
// show stock, give an option to add or remove and cancel
void stockMenu(vector <Stock>* stockList) // TODO
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
            cout << "2. Add to Stock" << endl;
            limh();
            cout << "3. Remove from Stock" << endl;
            limh();
            cout << "4. Go Back" << endl;
            limh();
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, productsOpt));

        switch (productsOpt)
        {
        case 1:
            printStockFile();
            break;
        case 2:
            addPurchaseToStock(stockList);
            break;
        
        case 3:
            removePurchaseFromStock();
            break;
        case 4:
            stockMenu = false;
            break;
        
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }
        
    } while (stockMenu);
    
}