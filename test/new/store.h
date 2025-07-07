#pragma once

#include <vector>
#include <array>

#include "menu.h"
#include "stock.h"
#include "cartItem.h"
#include "receipt.h"
#include "client.h"
#include "salesReport.h"
#include "fileManager.h"
#include "utils.h"

using namespace std;

class Store
{
private:
    vector<Stock> stockList;
    vector<Stock> shelf;
    vector<CartItem> cart;
    vector<Client> clientList;
    array<Receipt, 100> salesList; // Did all the receipt logic for the reports here, so thats what we save ig

    bool dataInit();
    bool dataUpdate();
    bool shelfInit();

public:
    Menu menu;
    Store(); // constructs with a stock menu and a sales menu

    vector<Stock> &getStock();
    vector<Stock> &getShelf();
    vector<CartItem> &getCart();
    vector<Client> &getClientList();
    array<Receipt, 100> &getSalesList();

    // Stock Management
    Stock *findStockById(int stockId);
    Stock *findStockByName(const string &name);
    vector<Stock> searchPurchaseStock(const string &name);
    void addPurchaseStock(Stock *item);
    void changeQuantityStock(Stock *item, int quantity);
    void changePurchaseStock(Stock *olditem, Stock newitem);
    void removePurchaseStock(Stock *item);
    void updateStockFromShelf();

    // Cart Management
    CartItem *findItemCart(int id, int *index = nullptr);
    Stock *findShelf(int stockId);
    void clearCart(vector<Stock> *shelf = nullptr); // check implementation

    // Client Management
    Client *findClientById(int clientId);
    Client *findClientByName(const string &name);
    void addClient(Client &newClient);
    bool removeClient(int clientId);

    // Sales Management
    double calculateCartTotal();
};