#include "utils.h"

#include "stock.h"
#include "cartItem.h"
#include "client.h"
#include "receipt.h"
#include "fileManager.h"

#include <iostream>  // will need this for cin and cout
#include <iomanip>   // will need this for setw
#include <string>    // will need this for the string class
#include <fstream>   // will need this for file handling
#include <sstream>   // will need this for string stream
#include <algorithm> // will need this for sorting and searching
#include <vector>    // will need for stock vector list
#include <regex>     // will need this for regex validation

using namespace std;

void pause() // pause the console
{
    cout << "Press enter to continue...";
    cin.ignore();
}

void limh(int n) // horizontal line with color
{
    cout << Magenta << string(n, '-') << RESET << endl;
}

void clearConsole() // clear the console
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}

// default prompt -> "Do you wish to continue?"
// prints as -> "Do you wish to continue (y̲/n)?"
bool promptYESOrNo(string prompt)
{
    string input;
    while (true)
    {
        cout << prompt << " (" << UNDERLINE << "y" << RESET << "/n): ";
        getline(cin, input);
        input = stringToLower(input);

        if (input == "y" || input.empty())
            return true;
        else if (input == "n")
            return false;
        else
            cout << "Invalid input. Please enter 'y' or 'n' or press enter for default." << endl;
    }
}

// default prompt -> "Do you wish to continue?"
// prints as -> "Do you wish to continue (y/n̲)?"
bool promptyesOrNO(string prompt)
{
    string input;
    while (true)
    {
        cout << prompt << " (y/" << UNDERLINE << "n" << RESET << "): ";
        getline(cin, input);
        input = stringToLower(input);

        if (input == "n" || input.empty())
            return false;
        else if (input == "y")
            return true;
        else
            cout << "Invalid input. Please enter 'y' or 'n' or press enter for default." << endl;
    }
}

// returns true if number is validated, false if not
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

int getValidatedInt(const string &prompt, bool zero)
{
    string input;
    int value;
    regex pattern("^\\d+$"); // Matches only positive integers (no minus sign, no letters)

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (!regex_match(input, pattern))
        {
            cout << "Invalid input. Please enter a positive whole number." << endl;
            continue;
        }
        try
        {
            value = stoi(input);
            if (value == 0 && zero == false)
            {
                cout << "Value must be greater than zero." << endl;
                continue;
            }
            return value;
        }
        catch (...)
        {
            cout << "Number is out of range. Try a smaller value." << endl;
        }
    }
}

double getValidatedDouble(const string &prompt)
{
    const double maxValue = 1000000.00; // Arbitrary maximum
    string input;
    double value;
    regex pattern("^\\d+(\\.\\d{1,2})?$"); // Matches only positive integers with up to two decimal places

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (!regex_match(input, pattern))
        {
            cout << "Invalid input. Please enter a positive number with up to two decimals." << endl;
            continue;
        }
        try
        {
            value = stod(input);
            if (value <= 0.0)
            {
                cout << "Value must be greater than zero." << endl;
                continue;
            }
            if (value > maxValue)
            {
                cout << "Value exceeds allowed maximum of €" << fixed << setprecision(2) << maxValue << "." << endl;
                continue;
            }
            return value;
        }
        catch (...)
        {
            cout << "Number is out of range. Try a smaller value." << endl;
        }
    }
}
string getValidatedName()
{
    regex nameRegex(R"(^[A-Z][a-zA-Z]+\s+[A-Z][a-zA-Z]+$)"); // Matches only first and last name
    string input;
    while (true)
    {
        cout << "Please insert client's first and last name (First Last): ";
        getline(cin, input);
        if (!regex_match(input, nameRegex))
        {
            cout << endl
                 << "Invalid client name. Please make sure to enter a first and a last name." << endl;
            continue;
        }
        else
            return input;
    }
}
string getValidatedAddress()
{
    regex addressRegex(R"(^([A-Za-zÀ-ÿ\s]+),\s*(\d+),\s*([A-Za-zÀ-ÿ\s]+)$)"); // Matches only adresses (street, door, city)
    string input;
    while (true)
    {
        cout << "Please insert client's address (Street, Door number, City): ";
        getline(cin, input);
        if (!regex_match(input, addressRegex))
        {
            cout << endl
                 << "Invalid client address. Please make sure to enter address in the following format: Street, Door number, City." << endl;
            continue;
        }
        else
        {
            input = regex_replace(input, regex(","), "");
        }
        return input;
    }
}
int getValidatedContact()
{
    regex phoneRegex(R"(^9\d{8}$)"); // Matches only valid phone numbers (9xxxxxxxx)
    string input;
    while (true)
    {
        cout << "Please insert client's phone number (9xxxxxxxx): ";
        getline(cin, input);
        if (!regex_match(input, phoneRegex))
        {
            cout << endl
                 << "Invalid client contact. Please make sure to enter a valid phone number, 9 digits, starting with 9." << endl;
            continue;
        }
        else
            return stoi(input);
    }
}

void setColor(const string &colorCode)
{
    cout << colorCode;
}

string stringToLower(string name)
{
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    return lowerName;
}

// void printStock(const vector<Stock> &stockList, const string &title, vector<int> *idColor, const string colorCode)
// {
//     clearConsole();
//     int titleDASH = STOCK_DASH - title.length(); // to make sure it fits the rest of the horizontal lims

//     setColor(YELLOW);
//     cout << title;
//     setColor(RESET);
//     limh(titleDASH);

//     setColor(CYAN);
//     cout << "ID | Product Name           | Quantity | Cost (eur)" << endl;
//     setColor(RESET);
//     limh();

//     for (const Stock &item : stockList)
//     {
//         if (item.getQuantity() == 0)
//             setColor(RED); // red for zero quantity
//         if (idColor != nullptr)
//             for (int id : *idColor)
//             {
//                 if (item.getStockId() == id)
//                     setColor(colorCode); // <color> for when item matches vector idColor
//             }

//         cout << item.toDisplay() << endl;

//         setColor(RESET); // resets color
//     }

//     limh();
// }

// this function will only show relevant information to client
// ie.: client doesn't need to know the purchase value, only the sale value

// void printProducts(const vector<Stock> &shelf)
// {
//     // just for pretty formatting
//     int titleLength = 13;

//     clearConsole();
//     setColor(YELLOW);
//     cout << "Products View";
//     setColor(RESET);
//     limh(PRODUCTS_DASH - titleLength);

//     setColor(CYAN);
//     cout << "ID | Product Name           | Quantity | Price w/Tax (eur)" << endl;
//     setColor(RESET);
//     limh(PRODUCTS_DASH);

//     for (const Stock &item : shelf)
//     {
//         if (item.getQuantity() == 0)
//             setColor(RED); // red for zero quantity

//         stringstream ss;
//         cout << setw(2) << right << item.getStockId() << " | "
//              << setw(22) << left << item.getProductName() << " | "
//              << setw(8) << right << item.getQuantity() << " | "
//              << fixed << setprecision(2) << item.getSaleValue() * 1.23 << " eur"
//              << endl;

//         setColor(RESET); // resets color
//     }

//     limh(PRODUCTS_DASH);
// }

// // Prints items in cart similar to printStock()
// void printCart(vector<CartItem> &cart) // TODO
// {
//     int titleDASH = CART_DASH - 9; // to make sure it fits the rest of the horizontal lims
//     clearConsole();
//     setColor(YELLOW);
//     cout << "Your cart";
//     setColor(RESET);

//     limh(titleDASH);
//     setColor(CYAN);
//     cout << setw(2) << "ID" << " | "
//          << setw(22) << left << "Product Name" << " | "
//          << setw(5) << right << "Qtty" << " | "
//          << setw(12) << right << "Price" << " | "
//          << setw(12) << right << "Total"
//          << endl;
//     setColor(RESET);
//     limh(CART_DASH);
//     if (cart.empty())
//     {
//         cout << "Cart is empty." << endl;
//         limh(CART_DASH);
//         return;
//     }
//     for (const CartItem &cartItem : cart)
//     {
//         cout << cartItem.toDisplay() << endl;
//     }

//     limh(CART_DASH);
// }