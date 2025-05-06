#include "utils.h"

using namespace std;

// init static variables
int Stock::nextStockId = 1;
int Receipt::nextReceiptId = 1;
int Receipt::nextClientId = 1;

void pause() // pause the console
{
    cout << "Press enter to continue...";
    cin.ignore();
}

void limh() // horizontal line with color
{
    cout << "\033[0;35m---------------------------------------------------\033[0m" << endl;
}

void clearConsole() // clear the console
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
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
        getline(file, line); // ignores header
        int maxId = 0;

        while (getline(file, line))
        {
            Stock item;
            item.fromString(line);
            stockList->push_back(item);

            // Track the highest ID
            if (item.getStockId() > maxId)
                maxId = item.getStockId();
        }
        // Set the nextStockId to one greater than the highest existing ID
        Stock::setNextStockId(maxId + 1);
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
        file << "StockId,ProductName,Quantity,CostValue" << endl;
        for (Stock item : stockList)
        {
            file << item.toString() << endl;
        }
        cout << "Stock Updated!" << endl;
        return true;
    }
    else
    {
        cout << "Error opening file." << endl;
        return false;
    }
}

int dataInit(vector<Stock> &stockList)
{
    cout << "Opening Stock File... ";
    createStockFile();
    if (openStockFile(&stockList))
    {
        cout << "Success!" << endl;
        pause();
        return 0;
    }
    else
    {
        cout << "Error!" << endl;
        pause();
        return 1;
    }
}

void addPurchaseToStock(vector<Stock> &stockList)
{
    string filename = "output/stockList.csv";
    string confirm;

    vector<int> idColor; // saves ids for marking when changed

    do
    {
        printStock(stockList, "Add Item Menu", idColor, "\033[0;32m");
        /*clearConsole();
        setColor("\033[1;33m");
        cout << "Register a purchase: " << endl;
        setColor("\033[0m");
        limh();

        setColor("\033[1;36m");
        cout << "ID | Product Name           | Quantity | Cost eur" << endl;
        setColor("\033[0m");
        limh();

        int colorMarker = 0;

        for (const Stock &item : stockList)
        {
            for (int i : ids) // checks if item was introduced recently and sets color to green
            {
                if (item.getStockId() == i)
                {
                    colorMarker = 1;
                    break;
                }
            }
            if (item.getQuantity() == 0)
                colorMarker = 2;

            if (colorMarker == 2)
                setColor("\033[1;31m"); // red for zero quantity
            else if (colorMarker == 1)
                setColor("\033[0;32m"); // green for recent addition

            cout << item.toDisplay() << endl;

            setColor("\033[0m"); // resets color
            colorMarker = 0;
        }
        limh();*/

        Stock item;
        stringstream line;
        string field;
        cout << "Product Name (leave empty to go back): ";

        getline(cin, field);
        if (field.empty())
            return;
        item.setProductName(field);

        Stock *findItem;
        string name = item.getProductName();
        if (findPurchaseFromStock(stockList, findItem, name) && findItem != nullptr)
        {
            cout << endl
                 << "Product Name was found in stockpile, do you want to add to product quantity? (y/n): ";
            getline(cin, confirm);
            confirm = stringToLower(confirm);
            if (confirm == "y")
            {
                item.setStockId(findItem->getStockId());
                item.setCostValue(findItem->getCostValue());
                item.setProductName(findItem->getProductName());

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
            item.setStockId(Stock::getNextStockId());
            Stock::incrementStockId();
            item.setQuantity(getValidatedInt("Quantity: "));
            item.setCostValue(getValidatedDouble("Cost Value: "));

            stockList.push_back(item);
            updateFile(stockList);
        }
        idColor.push_back((item.getStockId()));

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
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *&item, int id)
{
    // ID == vector index
    item = nullptr;
    if (stockList.empty())
    {
        cout << "Stock is empty!" << endl;
        return false;
    }
    if (id > stockList.size())
    {
        cout << "No matching ID in stock" << endl;
        return false;
    }
    item = &stockList.at(id - 1); // copies address of corresponding <Stock> object to <Stock> pointer item

    return true;
}

// OVERLOADED
// finds product in vector by name
// passes item by reference:
// item --> item in vector
// returns true if found, false if not found
bool findPurchaseFromStock(vector<Stock> &stockList, Stock *&item, const string &name)
{
    item = nullptr;
    if (stockList.empty())
    {
        return false;
    }
    // Read the stockList vector and search for the item by name
    string tolowerName = stringToLower(name);

    //  problem -> for cycle was copying the value of the found item to <findItem>, instead of copying the reference
    //  to avoid this, we cycle through items in stock using references, thus not making any copies, using the correct value
    for (Stock &findItem : stockList)
    {
        //  checking if any item matches argument name
        string tolowerProduct = stringToLower(findItem.getProductName());
        if (tolowerProduct == tolowerName)
        {
            item = &findItem; // copies address of corresponding <Stock> object to <Stock> pointer item
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
    setColor("\033[1;33m");
    cout << "Search Results:" << endl;
    setColor("\033[0m");
    if (items.empty())
    {
        limh();
        setColor("\033[1;36m");
        cout << "No matching results found" << endl;
        setColor("\033[0m");
        limh();
    }
    else
    {
        setColor("\033[0;35m");
        cout << "Found " << items.size() << " matching results:" << endl;
        setColor("\033[0m");
        limh();

        setColor("\033[1;36m");
        cout << "ID | Product Name           | Quantity | Cost eur" << endl;
        setColor("\033[0m");
        limh();

        for (const Stock &item : items)
        {
            if (item.getQuantity() == 0)
                setColor("\033[1;31m"); // red for zero quantity

            cout << item.toDisplay() << endl;

            if (item.getQuantity() == 0)
                setColor("\033[0m"); // resets color
        }
        limh();
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
    if (findPurchaseFromStock(stockList, item, id))
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
void changePurchaseFromStock(vector<Stock> &stockList, Stock *olditem, Stock newitem)
{
    olditem->setProductName(newitem.getProductName());
    olditem->setQuantity(newitem.getQuantity());
    olditem->setCostValue(newitem.getCostValue());

    updateFile(stockList);
}

void printStock(const vector<Stock> &stockList, const string &title)
{
    clearConsole();
    setColor("\033[1;33m");
    cout << title;
    setColor("\033[0m");
    
    limh();
    setColor("\033[1;36m");
    cout << "ID | Product Name           | Quantity | Cost (eur)" << endl; // fix euro symbol €
    setColor("\033[0m");
    limh();
    
    for (const Stock &item : stockList)
    {
        if (item.getQuantity() == 0)
        setColor("\033[1;31m"); // red for zero quantity
        
        cout << item.toDisplay() << endl;
        
        setColor("\033[0m"); // resets color
    }
    
    limh();
    pause();
}

void printStock(const vector<Stock> &stockList, const string &title, vector<int> idColor, const string colorCode)
{
    clearConsole();
    setColor("\033[1;33m");
    cout << title;
    setColor("\033[0m");
    
    limh();
    setColor("\033[1;36m");
    cout << "ID | Product Name           | Quantity | Cost (eur)" << endl; // fix euro symbol €
    setColor("\033[0m");
    limh();
    
    for (const Stock &item : stockList)
    {
        if (item.getQuantity() == 0)
        setColor("\033[1;31m"); // red for zero quantity
        for (int id : idColor)
        {
            if (item.getStockId() == id)
            setColor(colorCode);    // <color> for when item matches vector idColor
        }
        
        cout << item.toDisplay() << endl;
        
        setColor("\033[0m"); // resets color
    }
    
    limh();
    pause();
}
/*
void printStock(const vector<Stock> &stockList)
{
    clearConsole();
    setColor("\033[1;33m");
    cout << "Stock:\n";
    setColor("\033[0m");

    limh();
    setColor("\033[1;36m");
    cout << "ID | Product Name           | Quantity | Cost (eur)" << endl; // fix euro symbol €
    setColor("\033[0m");
    limh();

    for (const Stock &item : stockList)
    {
        if (item.getQuantity() == 0)
            setColor("\033[1;31m"); // red for zero quantity

        cout << item.toDisplay() << endl;

        if (item.getQuantity() == 0)
            setColor("\033[0m"); // resets color
    }

    limh();
    pause();
}
    */