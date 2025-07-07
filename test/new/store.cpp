#include "store.h"

// private
bool Store::dataInit()
{
    int errorCheck = 0;
    errorCheck += FileManager::loadStock(this->stockList);
    errorCheck += FileManager::loadClients(this->clientList);
    errorCheck += FileManager::loadReceipts(this->salesList);

    if (errorCheck != 5)
        return false;
    return true;
}

bool Store::dataUpdate()
{
    int errorCheck = 0;
    errorCheck += FileManager::saveStock(this->stockList);
    errorCheck += FileManager::saveClients(this->clientList);
    errorCheck += FileManager::saveReceipts(this->salesList);

    if (errorCheck != 5)
        return false;
    return true;
}

void Store::updateStockFromShelf()
{
    for (Stock &shelf_item : shelf)
    {
        int id = shelf_item.getStockId();
        Stock *stock_item = Store::findStockById(id);
        Store::changePurchaseStock(stock_item, shelf_item);
    }
    cout << "Stock Updated!" << endl;
}

// public
Store::Store() : menu(*this)
{
    if (Store::dataInit() == false)
    {
        string buffer;
        cout << "Error: Failed to load data base. Please check with the developers!" << endl;
        cout << "Please enter Ctrl + C to kill task.";
        getline(cin, buffer);
    }
}

// Stock Management
vector<Stock> &Store::getStock()
{
    return stockList;
}
vector<Stock> &Store::getShelf()
{
    return shelf;
}

Stock *Store::findStockById(int stockId)
{
    for (Stock &stock : stockList)
    {
        if (stock.getStockId() == stockId)
            return &stock;
    }
    return nullptr;
}

Stock *Store::findStockByName(const string &name)
{
    string lowerName = stringToLower(name);
    for (Stock &stock : stockList)
    {
        if (stringToLower(stock.getProductName()) == lowerName)
            return &stock;
    }
    return nullptr;
}

vector<Stock> Store::searchPurchaseStock(const string &name)
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

void Store::removePurchaseStock(Stock *item)
{
    item->setQuantity(0);
    FileManager::saveStock(stockList);
}

void Store::addPurchaseStock(Stock *item)
{
    stockList.push_back(*item);
    if (FileManager::saveStock(stockList))
        cout << "Stock Updated!" << endl;
    cout << endl
         << "Item ID: " << item->getStockId() << " added in stockpile!" << endl;
}

void Store::changeQuantityStock(Stock *item, int quantity)
{
    item->setQuantity(quantity);
    FileManager::saveStock(stockList);
}

void Store::changePurchaseStock(Stock *olditem, Stock newitem)
{
    olditem->setProductName(newitem.getProductName());
    olditem->setQuantity(newitem.getQuantity());
    olditem->setCostValue(newitem.getCostValue());

    FileManager::saveStock(stockList);
}

// Client Management
void Store::addClient(Client &newClient)
{
    clientList.push_back(newClient);
    return;
}

bool Store::removeClient(int id)
{
    Client *killClient = findClientById(id);
    if (killClient != nullptr)
    {
        killClient->switchActive();
        return true;
    }
    else
        return false;
}

Client *Store::findClientById(int clientId)
{
    for (Client &client : clientList)
    {
        if (client.getClientId() == clientId)
            return &client;
    }
    return nullptr;
}

Client *Store::findClientByName(const string &name)
{
    string lowerName = stringToLower(name);
    for (Client &client : clientList)
    {
        if (stringToLower(client.getName()) == lowerName)
            return &client;
    }
    return nullptr;
}

// Sales Management

double Store::calculateCartTotal()
{
    double total = 0;
    for (const CartItem &item : cart)
    {
        total += item.getTotalItemSellValue();
    }
    return round(total * 100) / 100;
}