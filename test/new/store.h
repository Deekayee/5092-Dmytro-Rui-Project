#pragma once

#include <vector>
#include <array>

#include "menu.h"
#include "stock.h"
#include "cartItem.h"
#include "receipt.h"
#include "client.h"
#include "fileManager.h"
#include "utils.h"

using namespace std;

class Store
{
private:
    vector<Stock> stockList;
    vector<CartItem> cart;
    vector<Stock> shelf;
    vector<Client> clientList;
    array<Receipt, 100> receiptList;

    bool dataInit();
    bool dataUpdate();
    void updateStockFromShelf();

public:
    Menu menu;
    Store(); // constructs with a stock menu and a sales menu

    vector<Stock>& getStock();

    // Stock Management
    Stock *findStockById( int stockId);
    Stock *findStockByName( const string &name);
    vector<Stock> searchPurchaseStock(const string &name);
    void addPurchaseStock (Stock *item);
    void changeQuantityStock( Stock *item, int quantity);
    void changePurchaseStock( Stock *olditem, Stock newitem);
    void removePurchaseStock( Stock *item);
    void printStock(const string &title, vector<int> *idColor = nullptr, const string colorCode = "");
    void printProducts();

    // Cart Management
    CartItem *findItemCart(int id, int *index = nullptr);
    void addProductCart(bool menuState); // menu
    void removeProductCart(bool menuState); // menu
    void changeProductCart(bool menuState); // menu
    void clearCart(vector<Stock> *shelf = nullptr); // check implementation
    void printCart();

    // Client Management
    Client *findClientById(int clientId);
    Client *findClientByName(const string &name);
    void addClient(Client &newClient);
    void removeClient(int clientId);
    void printClients(); // menu

    // Sales Management
    void checkoutMenu(); // menu
    double calculateCartTotal();
    Client *handleClientSelection(); // menu
    Client *createNewClient(); // menu
    double processPayment(double total);
    void completeCheckout(Client *client, double payment, double total); //maybe // menu
    void gambling(vector<CartItem> &sale, int chance = 50);


};
