#include "store.h"

// private
bool dataInit()
{
    int errorCheck = 0;
    errorCheck += fileManager::loadStock();
    errorCheck += fileManager::loadCart();
    errorCheck += fileManager::loadShelf();
    errorCheck += fileManager::loadClient();
    errorCheck += fileManager::loadSale();

    if (errorCheck != 5)
        return false;
    return true;
}

bool dataUpdate()
{
    int errorCheck = 0;
    errorCheck += fileManager::saveStock();
    errorCheck += fileManager::saveCart();
    errorCheck += fileManager::saveShelf();
    errorCheck += fileManager::saveClient();
    errorCheck += fileManager::saveSale();

    if (errorCheck != 5)
        return false;
    return true;
}

// public
Store() : menu(*this)
{
    if (dataInit() = false)
    {
        cout << "Error: Failed to load data base. Please check with the developers!" << endl;
        cout << "Please enter Ctrl + C to kill task." getline();
    }
}

&vector<Stock> getStock() const { return &stockList; }
&vector<CartItem> getCart() const { return &cart; }
&vector<CartItem> getShelf() const { return &shelf; }
&vector<Client> getClients() const { return &clientList; }
&array<sale> getSales() const { return &salesList; }
