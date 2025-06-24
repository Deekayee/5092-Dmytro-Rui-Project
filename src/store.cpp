#include "../include/store.h"
#include "../include/utils.h"
#include "../include/fileManager.h"

Store::Store()
{
    // Initialize DataBase
    // - open stock, client and sale files
    // - fill stock and client vectors
    // - fill out sale *special* vector (limit 100)
    // - loadup start menu
    initializeData();
}

// Getters

vector<Stock> &Store::getStockList()
{
    return stockList;
}

vector<CartItem> &Store::getCart()
{
    return cart;
}

vector<Client> &Store::getClientList()
{
    return clientList;
}
array<Receipt, 100> Store::getSaleList()
{
    return saleList;
}

// Data Management

bool Store::initializeData()
{
    int errorCheck = 0;
    errorCheck += FileManager::loadStockFromFile("stockList.csv", stockList);
    errorCheck += FileManager::loadClientsFromFile("clientList.csv", clientList);
    errorCheck += FileManager::loadReceiptsFromFile("saleList.csv", saleList);

    if (errorCheck != 3)
        return false;
}

void Store::shelfInit(vector<Stock> &stockList, vector<CartItem> &cart, vector<Stock> &shelf)
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
            Stock *shelf_item = findStockById(shelf, cart_item.getStockId());
            int quantity = shelf_item->getQuantity() - cart_item.getQuantity();
            shelf_item->setQuantity(quantity);
        }
    }
}

// Stock Management

Stock *Store::findStockById(vector<Stock> &stockList, int stockId)
{
    for (Stock &stock : stockList)
    {
        if (stock.getStockId() == stockId)
            return &stock;
    }
    return nullptr;
}

Stock *Store::findStockByName(vector<Stock> &stockList, const string &name)
{
    string lowerName = stringToLower(name);
    for (Stock &stock : stockList)
    {
        if (stringToLower(stock.getProductName()) == lowerName)
            return &stock;
    }
    return nullptr;
}

vector<Stock> Store::searchForProduct(const string &name)
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

void Store::removePurchaseFromStock(vector<Stock> &stockList, Stock *item)
{
    item->setQuantity(0);
    FileManager::saveStockToFile("stockList.csv", stockList);
}

void Store::changeQuantityFromStock(vector<Stock> &stockList, Stock *item, int quantity)
{
    item->setQuantity(quantity);
    FileManager::saveStockToFile("stockList.csv", stockList);
}

void Store::printStock(const vector<Stock> &stockList, const string &title, vector<int> *idColor = nullptr, const string colorCode = "")
{
}

void Store::printProducts(const vector<Stock> &shelf)
{
}

// Cart Management

CartItem *Store::findItemCart(vector<CartItem> &cart, int id, int *index = nullptr)
{
}
void Store::addProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
}
void Store::removeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
}
void Store::changeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState)
{
}
void Store::clearCart(vector<CartItem> &cart, vector<Stock> *shelf = nullptr)
{
}

void Store::printCart(vector<CartItem> &cart)
{
}

// Client Management

Client *Store::findClientById(vector<Client> &clientList, int clientId)
{
}

Client *Store::findClientByName(vector<Client> &clientList, const string &name)
{
}

// Sales Management

void Store::checkoutMenu(vector<Stock> &stockList, vector<Stock> &shelf, vector<CartItem> &cart)
{

}

void Store::gambling(vector<CartItem> &sale, int chance)
{
    srand(time(0));
    int badLuck = (rand() % 101); // badluck goes from 0 to 100

    if (badLuck < chance) // if the "bad luck" is less than the chance, win
    {
        // vector<CartItem> roster = sale;

        srand(time(0));                         // reinitializing seed
        int sortedIndex = rand() % sale.size(); // randomizing index

        CartItem jackpot = sale.at(sortedIndex);
        cout << "You won a free " << jackpot.getProductName() << "!" << endl;
        jackpot.setQuantity(1); // client only gets one, >:(

        double fullPrice = jackpot.getSaleWithoutTax();
        // jackpot.setTaxRatePercent(0);        // Disable tax (don't apply again)
        jackpot.setSaleWithoutTax(-fullPrice); // Negate full price (as base)

        sale.push_back(jackpot); // item gets added at end of receipt for display
    }
}