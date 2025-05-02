#pragma once //  compiler only sees this lib file once
#include <iostream>
#include <string>    // will need this for the string class
#include <fstream>   // will need this for file handling
#include <sstream>   // will need this for string stream
#include <algorithm> // will need this for sorting and searching
#include <vector>    // will need for stock vector list
#include <regex>     // will need this for regex validation

#include "shopClasses.h" // my classes
using namespace std;
void clearConsole();
void limh();
void pause();

bool findPurchaseFromStock(vector<Stock> &stockList, Stock *item, const string &name);
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *item, int id);
void changePurchaseFromStock(vector<Stock> stockList, Stock *olditem, Stock newitem);

bool validateMenuInput(const string &input, int &opt)
{
    // Check if the string is entirely digits
    for (char ch : input)
    {
        if (!isdigit(ch) && ch != '.')
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

int getValidatedInt(const string &prompt)
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
            if (value == 0)
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

string stringToLower(string name)
{
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    return lowerName;
}

//  writes string to file, returns false if error
void writeToFile(string filename, const string &line)
{
    fstream file(filename, ios::app);
    if (file.is_open())
    {
        file << line << endl;
        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
        return;
    }
    return;
}

//  if the file doesn't exist, we create it, returns false if error
void createStockFile()
{
    if (!ifstream("output/stockList.csv"))
    {
        // gives the file a header
        writeToFile("output/stockList.csv", "StockId,ProductName,Quantity,CostValue");
    }
}

//  will validate pointer to vector and returns stockList by reference
bool openStockFile(vector<Stock> *stockList)
{
    fstream file("output/stockList.csv", ios::in);
    if (file.is_open() && stockList != nullptr)
    {
        string line;
        getline(file, line); //  ignores header
        while (getline(file, line))
        {
            Stock item;
            item.fromString(line);
            stockList->push_back(item);
        }
    }
    else
    {
        cout << "Error opening file." << endl;
        return false;
    }

    return true;
}

bool updateFile(vector<Stock> &stockList)
{
    //  opens in truncate mode (overwrites)
    ofstream file("output/stockList.csv");
    if (file.is_open())
    {
        file << "StockId,ProductName,Quantity,CostValue" << endl; // FIX this here
        for (Stock item : stockList)
        {
            file << item.toString() << endl;
        }
        return true;
    }
    else
    {
        cout << "Error opening file." << endl;
        return false;
    }
}

void addPurchaseToStock(vector<Stock> &stockList)
{
    Stock item;
    string filename = "output/stockList.csv";
    string confirm;

    clearConsole();
    cout << "Register a purchase " << endl;
    do
    {
        stringstream line;
        string field;
        limh();
        // added autoincrement, so this is unnecessary - Awesome!
        // needs user validation

        cout << "Product Name: ";
        getline(cin, field);
        item.setProductName(field);

        // write to file here
        // need search function for stock verification purposes
        // ie quantity needs to be > 0
        Stock *findItem;
        string name = item.getProductName();
        if (findPurchaseFromStock(stockList, findItem, name))
        {
            cout << endl
                 << "Product Name was found in stockpile, do you want to add to product quantity? (y/n): ";
            getline(cin, confirm);
            confirm = stringToLower(confirm);
            if (confirm == "y")
            {
                item.setStockId(findItem->getStockId());
                item.setCostValue(findItem->getCostValue());
                item.setProductName(findItem->getProductName()); // SEGFAULTS HERE for some

                int addedQuantity = getValidatedInt("Quantity to add: ");
                item.setQuantity(findItem->getQuantity() + addedQuantity);

                changePurchaseFromStock(stockList, findItem, item);
                cout << endl
                     << "Item ID: " << item.getStockId() << " changed in stockpile!" << endl;
                pause();
            }
        }
        else
        {
            item.setQuantity(getValidatedInt("Quantity: "));
            item.setCostValue(getValidatedDouble("Cost Value: "));

            stockList.push_back(item);
        }

        updateFile(stockList);

        cout << "Do you want to register another item? (y/n): ";
        getline(cin, confirm);
        confirm = stringToLower(confirm);
    } while (confirm == "y");
}

// OVERLOADED
// finds product in vector by id
// passes item by reference:
// item --> item in vector
// returns true if found, false if not found
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *item, int id) // fucked something here, gotta FIX (Fixed?)
{
    // ID == vector index
    if (id >= stockList.size())
    {
        return false;
    }

    item = new Stock;         // allocates memory for the pointer
    item = &stockList.at(id); // copies address of corresponding <Stock> object to <Stock> pointer item

    return true;
}

// OVERLOADED
// finds product in vector by name
// passes item by reference:
// item --> item in vector
// returns true if found, false if not found
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *item, const string &name)
{
    // Read the stockList vector and search for the item by name
    string tolowerName = stringToLower(name);

    //  problem -> for cycle was copying the value of the found item to <findItem>, instead of copying the reference
    //  to avoid this, we cycle through items in stock using references, thus not making any copies, using the correct value
    for (Stock &findItem : stockList)
    {
        //  checking if any item matches argument name
        string tolowerProduct = findItem.getProductName();
        tolowerProduct = stringToLower(tolowerProduct);
        if (tolowerProduct == tolowerName)
        {
            *item = findItem; // copies address of corresponding <Stock> object to <Stock> pointer item
            return true;
        }
    }
    return false;
}

//  not asked for, just sorta useful
vector<Stock> searchForProduct(vector<Stock> &stockList, const string &name)
{
    vector<Stock> items;
    string lowerName = stringToLower(name);
    for (Stock i : stockList)
    {
        string lowerProduct = stringToLower(i.getProductName());
        if (lowerProduct.find(lowerName) != string::npos)
        {
            items.push_back(i);
        }
    }
    return items;
}

bool showSearchResults(vector<Stock> items)
{
    clearConsole();
    if (items.empty())
    {
        cout << "No matching results found" << endl;
    }
    else
    {
        cout << "Found " << items.size() << " matching results:" << endl;
        for (Stock match : items)
        {
            cout << match.toString() << endl;
        }
    }

    char confirm;
    cout << "Do you wish to keep searching? (y/n): ";
    cin >> confirm;
    confirm = tolower(confirm);
    cin.ignore();
    if (confirm == 'y')
        return true;
    else
        return false;
}

//  Will use to delete a deleteNo from an item, (setQuantity to 0) in stockList vector
//  returns true if successful, false if not (product not found)
//  updates file
bool removePurchaseFromStock(vector<Stock> &stockList, int id)
{
    Stock *item;
    if (findPurchaseFromStock(stockList, item, id)) // fucked something here, gotta FIX
    {
        item->setQuantity(0);

        updateFile(stockList);
        return true;
    }
    else
        return false;
}

// searches for name and changes
//  Will use to replace object in stockList vector
//  uses item argument to search in stock for same !!!NAME!!!, and updates if found
//  returns true if successful, false if not (product not found)
//  updates file on success
void changePurchaseFromStock(vector<Stock> stockList, Stock *olditem, Stock newitem)
{
    olditem->setProductName(newitem.getProductName());
    olditem->setQuantity(newitem.getQuantity());
    olditem->setCostValue(newitem.getCostValue());

    updateFile(stockList);
}

void printStock()
{
    string line;

    clearConsole();
    cout << "Stock: " << endl;
    limh();
    ifstream fr("output/stockList.csv");
    if (fr.is_open())
    {
        while (getline(fr, line))
        {
            limh();
            cout << line << endl;
        }
        fr.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    limh();
    pause();
}
