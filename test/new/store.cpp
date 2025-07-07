#include "store.h"
#include <climits>

// private
bool Store::dataInit()
{
    
     FileManager::loadStock(this->stockList);
     FileManager::loadClients(this->clientList);
     FileManager::loadReceipts(this->salesList);
     Store::shelfInit();

    
    
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

void Store::shelfInit()
{
    // only allow client to view and select available stock through shelf
    shelf.clear();
    for (Stock &stock_item : stockList)
    {
        if (stock_item.getQuantity() == 0)
            continue;

        shelf.push_back(stock_item); // all items in shelf will be of quantity > 0
    }
    //once shelf is filled up, compare with cart, if its not empty
    if (!cart.empty())
    {
        for (CartItem &cart_item : cart)
        {
            Stock *shelf_item = findShelf(cart_item.getStockId());
            int quantity = shelf_item->getQuantity() - cart_item.getQuantity();
            shelf_item->setQuantity(quantity);
        }
    }
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
vector<CartItem> &Store::getCart()
{
    return cart;
}
vector<Client> &Store::getClientList()
{
    return clientList;
}
array<Receipt, 100> &Store::getSalesList()
{
    return salesList;
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

CartItem *Store::findItemCart(int id, int *index)
{
    for (int i = 0; i < cart.size(); i++)
    {
        if (cart.at(i).getStockId() == id)
        {
            if (index != nullptr)
                *index = i;
            return &cart.at(i); // finds and returns reference to item
        }
    }
    return nullptr;
}

Stock *Store::findShelf(int stockId)
{
    for (Stock &stock : shelf)
    {
        if (stock.getStockId() == stockId)
            return &stock;
    }
    return nullptr;
}

void Store::clearCart(vector<Stock> *shelf)
{
    if (cart.empty())
    {
        cout << "Cart is already empty" << endl;
        pause();
        return;
    }

    // *this case represents a canceled sale through the menu
    // here we need to bring back the quantities in the cart back to the shelf
    // before deleting them
    if (shelf != nullptr)
        for (CartItem &bagged_item : cart)
        {
            // update
            Stock *item = findShelf(bagged_item.getStockId());
            item->setQuantity(bagged_item.getQuantity() + item->getQuantity());
        }

    // *otherwise, if shelf isnt specified, it means checkout is happening, so
    // the shelf already owns the correct quantities and is ready to update our
    // stockList
    cart.clear();
    cout << "Cart cleared." << endl;
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

void Store::addReceipt(const Receipt &receipt)
{    
    // Find the first empty slot in the array
    int oldestId = INT_MAX;
    int oldestIndex;
    for (int i = 0; i < 100; i++)
    {
        int currentId = salesList.at(i).getReceiptId();
        // Check which slot has the lowest id (lower id means older receipt, as)
        if (currentId < oldestId)
        {
            oldestId = currentId;
            oldestIndex = i;
        }
    }
    salesList.at(oldestIndex) = receipt;
    return;
}