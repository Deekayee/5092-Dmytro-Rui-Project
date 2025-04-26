#pragma once //  compiler only sees this lib file once
#include <iostream>
#include <string>    // will need this for the string class
#include <fstream>   // will need this for file handling
#include <sstream>   // will need this for string stream
#include <algorithm> // will need this for sorting and searching
#include <vector>    // will need for stock vector list

#include "shopClasses.h" // my classes
using namespace std;
void clearConsole();
void limh();
void pause();

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

bool updateFile(vector<Stock> *stockList)
{
    ofstream file("output/stockList.csv");
    if (file.is_open())
    {
        file << "StockId,ProductName,Quantity,CostValue" << endl; // FIX this here
        for (Stock item : *stockList)
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

void addPurchaseToStock(vector<Stock> *stockList)
{
    Stock item;
    string filename = "output/stockList.csv";
    char confirm;

    clearConsole();
    cout << "Register a purchase: " << endl;
    do
    {
        stringstream line;
        string field;
        limh();
        // added autoincrement, so this is unnecessary
        // cout << "Item ID: ";
        // getline(cin, field);
        // line << field << ',';

        cout << "Product Name: ";
        getline(cin, field);
        item.setProductName(field);

        cout << "Quantity: ";
        getline(cin, field);
        item.setQuantity(stoi(field));

        cout << "Cost Value: ";
        getline(cin, field);
        item.setCostValue(stod(field));

        // write to file here
        // need search function for stock verification purposes
        // for now, will write into vector, then file
        stockList->push_back(item);
        writeToFile(filename, item.toString());

        cout << "Do you want to register another item? (y/n): ";
        cin >> confirm;
        confirm = tolower(confirm);
        cin.ignore();
    } while (confirm == 'y');
}

// finds product in vector
// passes fstream and item by reference:
// item --> item in vector
// returns true if found, false if not found
bool findPurchaseFromStock(vector<Stock> *stockList, Stock *item, int id) // fucked something here, gotta FIX
{
    // Read the stockList.csv file and search for the item
    if (id >= stockList->size())
    {
        return false;
    }
    item = &stockList->at(id); // copies address of corresponding <Stock> object to <Stock> pointer item

    return true;
}

vector<Stock> searchForProduct(vector<Stock> *stockList, const string &name)
{
    vector<Stock> items;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    for (Stock i : *stockList)
    {
        string lowerProduct = i.getProductName();
        transform(lowerProduct.begin(), lowerProduct.end(), lowerProduct.begin(), ::tolower);
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

    cout << "Here is the list of matching results:" << endl;
    for (Stock match : items)
    {
        cout << match.toString() << endl;
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

//  Will use to delete (setQuantity to 0) in stockList vector
//  returns true if successful, false if not (product not found)
bool removePurchaseFromStock(vector<Stock> *stockList, int id)
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

//  Will use to replace object in stockList vector
//  returns true if successful, false if not (product not found)
bool changePurchaseFromStock(vector<Stock> *stockList, int id, const string &line)
{
    Stock *item;
    if (findPurchaseFromStock(stockList, item, id)) // fucked something here, gotta FIX
    {
        item->fromString(line);
        updateFile(stockList);
        return true;
    }
    else
        return false;
}

void printStock() // TODO
{
    // vars
    string line;

    // open file
    clearConsole();
    cout << "Stock: " << endl;
    limh();
    ifstream fr("output/stockList.csv");
    if (fr.is_open())
    {
        while (getline(fr, line))
        {
            cout << line << endl;
        }
        fr.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    limh();
    pause();
}
