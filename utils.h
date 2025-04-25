#pragma once    //  compiler only sees this lib file once
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


void writeToFile(string filename, const string &line) // TODO #1
{
    fstream file(filename, ios::app);
    if (file.is_open())
    {
        file << line << endl;
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

void createStockFile()
{
    if (!ifstream("output/stockList.csv")) // if the file doesn't exist, we create it
    {
        writeToFile("output/stockList.csv", "StockId, ProductName, Quantity, CostValue"); // gives the file a header
    }
    ofstream file("output/stockList.csv", ios::app);
}

//  Will return a vector of Stock objects
vector <Stock> openStockFile()
{
    vector <Stock> stockList;
    fstream file("output/stockList.csv", ios::in);
    if (file.is_open())
    {
        string line;
        getline(file, line);                //  ignores header
        while (getline(file, line))
        {
            Stock item;
            item.fromString(line);
            stockList.push_back(item);
        }

    }else cout << "Error opening file." << endl;

    return stockList;
}

void addPurchaseToStock(vector <Stock>* stockList)
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
        cout << "Item ID: "; // this will change, as we want autoincrement ids
        getline(cin, field);
        line << field << ',';

        cout << "Product Name: ";
        getline(cin, field);
        line << field << ',';

        cout << "Quantity: ";
        getline(cin, field);
        line << field << ',';

        cout << "Cost Value: ";
        getline(cin, field);
        line << field;

        // write to file here
        item.fromString(line.str());
        // need search function for stock verification purposes
        // for now, will write into vector, then file
        stockList->push_back(item);
        writeToFile(filename, line.str());

        cout << "Do you want to register another item? (y/n): ";
        cin >> confirm;
        confirm = tolower(confirm);
        cin.ignore();
    } while (confirm == 'y');
}


//  need for stock menu: remove item (MY HOMEWORK)
void removePurchaseFromStock(){
    return;
}

//  Will use to make changes in stockList.csv
void changeLineFile(string filename, const string &line, const string &field)
{
}

void printStockFile() // TODO
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
    system("pause");
}

//  returns pointer to <Stock>, nullptr if none found
// needs rework
// Stock* findProduct()
// {
//     // Get the id to search for
//     int id;
//     clearConsole();
//     cout << "Finding a Product by ID" << endl;
//     limh();
//     cout << "Enter the ID of the product you want to find: ";
//     cin >> id;
    
//     // Read the stockList.csv file and search for the item
//     bool found = 0;
//     ifstream fr("stockList.csv");
//     if (fr.is_open())
//     {
//         string line;
//         string tmp;
//         Stock st;
//         //vector<Stock> items;
//         while (getline(fr, line))
//         {
//             st.fromString(line);
//             if(st.getStockId() == id)
//             {
//                 found = 1;
//                 break;
//             }
//         }
//         fr.close();
//         if (found)  return &st;
//         else 
//         {
//             cout << "No matching ID found" << endl;
//             return nullptr;
//         }
        
//     }
//     else
//     {
//         cout << "Unable to open file" << endl;
//         limh();
//     }
//     system("pause");
// }