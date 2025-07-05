#include "menu.h"
#include "utils.h"

// private:
//  Main() options:
void management()
{
    string input;
    int opt;
    while (true)
    {
        do
        {
            clearConsole();
            store.printStock("Stock View");

            setColor(Cyan);
            cout << "Stock Editing Menu" << endl;
            setColor(RESET);
            limh(STOCK_DASH);
            cout << "1. Search Stock" << endl;
            limh(STOCK_DASH);
            cout << "2. Add Stock" << endl;
            limh(STOCK_DASH);
            cout << "3. Change Stock" << endl;
            limh(STOCK_DASH);
            cout << "4. Remove Stock" << endl;
            limh(STOCK_DASH);
            cout << "0. Go Back" << endl;
            limh(STOCK_DASH);
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, opt));

        switch (opt)
        {
        case 1:
            searchStock();
            break;
        case 2:
            addStock();
            break;
        case 3:
            editStock();
            break;
        case 4:
            removeStock();
            break;
        case 0:
            return;
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }
    }
}

void shopping()
{
}

void logins()
{
}

// SubMenus - management:
void searchStock()
{
    bool run;
    do
    {
        clearConsole();
        store.printStock("Stock View");

        string name;
        setColor(Cyan);
        cout << "Stock Search Menu" << endl;
        setColor(RESET);
        limh(STOCK_DASH);
        cout << "Please enter a product name to search in stock" << endl;
        cout << "Name: ";
        getline(cin, name);

        vector<Stock> items = searchForProduct(stockList, name);
        run = showSearchResults(items);
    } while (run);
}

void addStock()
{
    vector<int> idColor; // saves ids for marking when changed

    do
    {
        clearConsole();
        store.printStock("Stock View", &idColor, Green);

        Stock item;
        stringstream line;
        string field;

        setColor(Cyan);
        cout << "Add Stock Menu" << endl;
        setColor(RESET);
        limh(STOCK_DASH);
        cout << "Product Name (leave empty to go back)" << endl;
        cout << "Name: ";

        getline(cin, field);
        if (field.empty())
            return;
        if (field.length() > STRING_PRODUCT_MAX) // to ensure name fits in tightly with the menu structure
        {
            cout << "Please enter a shorter name." << endl;
            pause();
            break;
        }

        item.setProductName(field);

        string name = item.getProductName();
        Stock *findItem = findStock(name);
        if (findItem != nullptr) // if product found
        {
            // default yes
            if (promptYESOrNo("Product Name was found in stockpile, do you want to add to product quantity?"))
            {
                int addedQuantity = getValidatedInt("Quantity to add: ");
                changeQuantityFromStock(store, findItem, addedQuantity + findItem->getQuantity());
                cout << endl
                     << "Item ID: " << findItem->getStockId() << " changed in stockpile!" << endl;
            }
        }
        else // if not found
        {
            item.setStockId(Stock::getNextStockId());
            Stock::incrementStockId();
            item.setQuantity(getValidatedInt("Quantity: "));
            item.setCostValue(getValidatedDouble("Cost Value: "));

            stockList.push_back(item);
            if (updateFile(stockList))
                cout << "Stock Updated!" << endl;
            cout << endl
                 << "Item ID: " << item.getStockId() << " added in stockpile!" << endl;
        }
        idColor.push_back((item.getStockId()));

        // default no
    } while (promptyesOrNO("Do you want to register another item?"));
}

void editStock()
{
    vector<int> idColor; // saves ids for marking when changed
    while (true)
    {
        clearConsole();
        printStock(stockList, "Change Item Menu", &idColor, Green);

        string prompt;
        int id;
        cout << "Please enter the ID of the product you wish to change (Enter 0 to return)" << endl;
        cout << "ID: ";
        getline(cin, prompt);

        if (!validateMenuInput(prompt, id))
            continue;

        if (id <= 0) // go back in menu
            return;

        Stock *item = findStock(stockList, id);
        if (item == nullptr)
        {
            cout << "Item not found in stock" << endl;
            pause();
            continue;
        }
        clearConsole();
        printStock(stockList, "Stock View");

        setColor(Cyan);
        cout << "Changing product: " << item->getStockId() << "-" << item->getProductName() << endl;
        setColor(RESET);
        limh();

        if (!promptYESOrNo("Do you wish to proceed?"))
        {
            continue;
        }
        limh(STOCK_DASH);

        stringstream itemString;
        itemString << item->getStockId() << ",";
        cout << "Enter new product data" << endl;
        cout << "Product name: ";
        getline(cin, prompt);
        itemString << prompt << ",";
        itemString << getValidatedInt("Quantity: ") << ",";
        itemString << getValidatedDouble("Cost: ");

        Stock newItem;
        newItem.fromString(itemString.str());
        changePurchaseFromStock(stockList, item, newItem);
        cout << "Stock Updated!" << endl;

        idColor.push_back(item->getStockId());

        if (!promptyesOrNO("Do you wish to keep editing items?"))
            return;
    }
}

void removeStock()
{
    vector<int> idColor; // saves ids for marking when changed
    while (true)
    {
        string prompt;
        int id;
        do
        {
            printStock(stockList, "Remove Item Menu", &idColor, Yellow);

            limh(STOCK_DASH);

            cout << "Please enter the ID of the product you wish to remove (Enter 0 to return)" << endl;
            cout << "ID: ";
            getline(cin, prompt);

        } while (!validateMenuInput(prompt, id));
        if (id <= 0) // go back in menu
            return;

        Stock *item = findStock(stockList, id);
        if (item == nullptr)
        {
            cout << "Item not found in stock" << endl;
            pause();
            continue;
        }
        if (item->getQuantity() == 0)
        {
            cout << "Item quantity already empty" << endl;
            pause();
            continue;
        }

        setColor(Cyan);
        cout << "Removing product: " << item->getStockId() << "-" << item->getProductName() << endl;
        setColor(RESET);
        if (!promptYESOrNo())
        {
            continue;
        }
        limh(STOCK_DASH);

        removePurchaseFromStock(stockList, item);
        cout << "Stock Updated!" << endl;

        if (!promptyesOrNO("Do you wish to keep removing items?"))
            return;
    }
}

// public:
Menu(Store &storeReference) : store(storeReference) {}

void main()
{
    string input;
    while (true)
    {
        do
        {
            clearConsole();
            setColor(Cyan);
            cout << "Shop menu" << endl;
            setColor(RESET);
            limh(STOCK_DASH);
            cout << "1. Shop Sales" << endl;
            limh(STOCK_DASH);
            cout << "2. Shop Stock" << endl;
            limh(STOCK_DASH);
            cout << "3. Exit" << endl;
            limh(STOCK_DASH);
            cout << "Option: ";
            getline(cin, input);
        } while (!validateMenuInput(input, opt));
    }

    switch (opt)
    {
    case 1:
        shopping();
        break;
    case 2:
        management();
        break;
    case 4:
        clearConsole();
        return;
    default:
        cout << "Invalid input, try again." << endl;
        pause();
        break;
    }
}
