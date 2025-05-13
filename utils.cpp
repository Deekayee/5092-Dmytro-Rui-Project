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
    if (!ifstream("stockList.csv"))
    {
        // gives the file a header
        cout << "Creating file..." << endl;
        writeToFile("stockList.csv", "StockId,ProductName,Quantity,CostValue");
    }
}

//  will validate pointer to vector and returns stockList by reference
bool openStockFile(vector<Stock> *stockList)
{
    fstream file("stockList.csv", ios::in);
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
    ofstream file("stockList.csv");
    if (file.is_open())
    {
        file << "StockId,ProductName,Quantity,CostValue" << endl;
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

void updateStockFromShelf(vector<Stock> &stockList, vector<Stock> &shelf)
{
    for (Stock &shelf_item : shelf)
    {
        int id = shelf_item.getStockId();
        Stock *stock_item = findStock(stockList, id);
        changePurchaseFromStock(stockList, stock_item, shelf_item);
    }
    cout << "Stock Updated!" << endl;
}

bool dataInit(vector<Stock> &stockList)
{
    cout << "Opening Stock File... " << endl;
    createStockFile();
    if (openStockFile(&stockList))
    {
        cout << "Success!" << endl;
        pause();
        return false;
    }
    else
    {
        cout << "Error!" << endl;
        pause();
        return true;
    }
}

void shelfInit(vector<Stock> &stockList, vector<CartItem> &cart, vector<Stock> &shelf)
{
    // only allow client to view and select available stock through shelf
    shelf.clear();
    for (Stock &stock_item : stockList)
    {
        if (stock_item.getQuantity() == 0)
            continue;

        shelf.push_back(stock_item); // all items in shelf will be of quantity > 0
    }
    // once shelf is filled up, compare with cart, if its not empty
    if (!cart.empty())
    {
        for (CartItem &cart_item : cart)
        {
            Stock *shelf_item = findStock(shelf, cart_item.getStockId());
            int quantity = shelf_item->getQuantity() - cart_item.getQuantity();
            shelf_item->setQuantity(quantity);
        }
    }
}

// OVERLOADED
// finds product in vector by id
// passes item by reference:
// item --> item in vector
// returns true if found, false if not found
Stock *findStock(vector<Stock> &stockList, int stockId)
{
    for (Stock &stock : stockList)
    {
        if (stock.getStockId() == stockId)
            return &stock;
    }
    return nullptr;
}

// OVERLOADED
// finds product in vector by name
// returns item address in stock:
// item --> item in vector
// returns nullptr if not found
Stock *findStock(vector<Stock> &stockList, const string &name)
{
    if (stockList.empty())
    {
        return nullptr;
    }
    // Read the stockList vector and search for the item by name
    string tolowerName = stringToLower(name);

    for (Stock &findItem : stockList)
    {
        //  checking if any item matches argument name
        string tolowerProduct = stringToLower(findItem.getProductName());
        if (tolowerProduct == tolowerName)
        {
            return &findItem; // returns address of corresponding <Stock> object storing it in a pointer
        }
    }
    return nullptr;
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

//  Will use to delete an item, (setQuantity to 0) in stockList vector
//  returns true if successful, false if not (product not found)
//  updates file
void removePurchaseFromStock(vector<Stock> &stockList, Stock *item)
{
    item->setQuantity(0);
    updateFile(stockList);
}

void changeQuantityFromStock(vector<Stock> &stockList, Stock *item, int quantity)
{
    item->setQuantity(quantity);
    updateFile(stockList);
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

void printStock(const vector<Stock> &stockList, const string &title, vector<int> *idColor, const string colorCode)
{
    clearConsole();
    int titleDASH = STOCK_DASH - title.length(); // to make sure it fits the rest of the horizontal lims

    setColor(YELLOW);
    cout << title;
    setColor(RESET);
    limh(titleDASH);

    setColor(CYAN);
    cout << "ID | Product Name           | Quantity | Cost (eur)" << endl;
    setColor(RESET);
    limh();

    for (const Stock &item : stockList)
    {
        if (item.getQuantity() == 0)
            setColor(RED); // red for zero quantity
        if (idColor != nullptr)
            for (int id : *idColor)
            {
                if (item.getStockId() == id)
                    setColor(colorCode); // <color> for when item matches vector idColor
            }

        cout << item.toDisplay() << endl;

        setColor(RESET); // resets color
    }

    limh();
}

// this function will only show relevant information to client
// ie.: client doesn't need to know the purchase value, only the sale value
void printProducts(const vector<Stock> &shelf)
{
    // just for pretty formatting
    int titleLength = 13;

    clearConsole();
    setColor(YELLOW);
    cout << "Products View";
    setColor(RESET);
    limh(PRODUCTS_DASH - titleLength);

    setColor(CYAN);
    cout << "ID | Product Name           | Quantity | Price w/Tax (eur)" << endl;
    setColor(RESET);
    limh(PRODUCTS_DASH);

    for (const Stock &item : shelf)
    {
        if (item.getQuantity() == 0)
            setColor(RED); // red for zero quantity

        stringstream ss;
        cout << setw(2) << item.getStockId() << " | "
             << setw(22) << left << item.getProductName() << " | "
             << setw(8) << right << item.getQuantity() << " | "
             << fixed << setprecision(2) << item.getSaleValue() * 1.23 << " eur"
             << endl;

        setColor(RESET); // resets color
    }

    limh(PRODUCTS_DASH);
}

// Prints items in cart similar to printStock()
void printCart(vector<CartItem> &cart) // TODO
{
    int titleDASH = CART_DASH - 9; // to make sure it fits the rest of the horizontal lims
    clearConsole();
    setColor(YELLOW);
    cout << "Your cart";
    setColor(RESET);

    limh(titleDASH);
    setColor(CYAN);
    cout << setw(2) << "ID" << " | "
         << setw(22) << left << "Product Name" << " | "
         << setw(5) << right << "Qtty" << " | "
         << setw(12) << right << "Price" << " | "
         << setw(12) << right << "Total"
         << endl;
    setColor(RESET);
    limh(CART_DASH);
    if (cart.empty())
    {
        cout << "Cart is empty." << endl;
        limh(CART_DASH);
        return;
    }
    for (const CartItem &cartItem : cart)
    {
        cout << cartItem.toDisplay() << endl;
    }

    limh(CART_DASH);
}