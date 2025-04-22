#include <iostream>
#include <string>    // will need this for the string class
#include <fstream>   // will need this for file handling
#include <sstream>   // will need this for string stream
#include <cctype>    // will need this for character validations
#include <algorithm> // will need this for sorting and searching
#include <cstdlib>   // for clearing the console
#include <vector>    // will need for stock vector list

#include "shopClasses.h" // my classes
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

void createStockFile(const string &filename)
{
    if (!ifstream(filename)) // if the file doesn't exist, we create it
    {
        writeToFile(filename, "StockId, ProductName, Quantity, CostValue"); // gives the file a header
    }
    ofstream file(filename, ios::app);
}

void addPurchaseToStock() // TODO
{
    Stock item;
    string line, filename = "stockList.csv";
    char confirm;

    clearConsole();
    cout << "Register a purchase: " << endl;
    do
    {
        limh();
        cout << "Item ID: "; // this will change, as we want autoincrement ids
        cin >> item.stockId;
        cin.ignore();

        cout << "Product Name: ";
        getline(cin, item.productName);

        cout << "Quantity: ";
        cin >> item.quantity;
        cin.ignore();

        cout << "Cost Value: ";
        cin >> item.costValue;
        cin.ignore();

        // write to file here
        line = to_string(item.stockId) + ", " + item.productName + ", " + to_string(item.quantity) + ", " + to_string(item.costValue);
        writeToFile(filename, line);

        cout << "Do you want to register another item? (y/n): ";
        cin >> confirm;
        confirm = tolower(confirm);
        cin.ignore();
    } while (confirm == 'y');
}

void readStockFile() // TODO
{
    // vars
    string line;

    // open file
    clearConsole();
    cout << "Stock: " << endl;
    limh();
    ifstream fr("stockList.csv");
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
            readStockFile();
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
void stockMenu() // TODO
{
    // show stock, give an option to add or remove and cancel
}

/*Sorting Criteria for stock vector*/
// Sort by Id
/*
bool lambdaId(const Stock &a, const Stock &b)
{
    return a.stockId < b.stockId;
}
// Sort by Quantity
bool lambdaQuantity(const Stock &a, const Stock &b)
{
    return a.quantity < b.quantity;
}
// Sort by Price (without tax)
bool lambdaPrice(const Stock &a, const Stock &b)
{
    return a.costWithoutTax < b.costWithoutTax;
}


// Read file function - will default to sorting the produced vector
vector<Stock> readFromFile(string filename)
{
    vector <Stock> stockItems; //declaration of our stock vector for our items
    fstream file(filename, ios::in);
    if (file.is_open())
    {
        string line; //will receive the entire line

        //now we go line by line, divide into substrings, and tranferring them into our new stock vector
        while (getline(file, line))
        {
            if(line.empty()) continue; //skip empty lines
            if(line.at(0) == '/' || line.at(0) == ' ' || line.at(1) == '*') continue; //ignore <stockName>.txt header

            stringstream stream_line(line); //stream version of line, for use in getline
            string str_aux; //getline destination for the newly partitioned string
            Stock item; //will receive useful data from the line out of stream_line

            //now we begin initializing our item
            getline(stream_line, str_aux, ',');// ID
            item.stockId = stoi(str_aux);

            getline(stream_line, item.productName, ',');// PRODUCT NAME

            getline(stream_line, str_aux, ',');// QUANTITY
            item.quantity = stoi(str_aux);

            getline(stream_line, str_aux);// COST NO TAX
            item.costWithoutTax = stod(str_aux);

            stockItems.push_back(item); // Add the complete item to the list
        }

    }else cout << "Error opening file." << endl;

    file.close();

    // Return with the sorted list of stockItems
    sort(stockItems.begin(), stockItems.end(), lambdaId);
    return stockItems;
}
//testing purposes only,
void printingTester(vector <Stock> list)
{
    for (Stock item : list)
    {
    //  Item ID n -> item name

        cout << "Item ID " << item.stockId << " -> " << item.productName << endl
        << "            |-" << item.quantity << endl
        << "            |-" << item.costWithoutTax << endl;
        limh();
    }
}
*/

// Write file function
// gotta decide how to handle the data, save it in a vector and then write it to the file or update the file directly
// file format: stockId,productName,quantity,costWithoutTax\n
