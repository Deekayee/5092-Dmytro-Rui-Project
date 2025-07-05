#pragma once

#include <vector>
#include <array>

#include "menu.h"
#include "stock.h"
#include "cartItem.h"
#include "client.h"
#include "saleReport.h"
#include "fileManager.h"
#include "utils.h"

using namespace std;

class Store
{
private:
    vector<Stock> stockList;
    vector<CartItem> cart;
    vector<CartItem> shelf;
    vector<Client> clientList;
    array<SaleReport, 100> salesList;

    bool dataInit();
    bool dataUpdate();

public:
    Menu menu;
    Store(); // constructs with a stock menu and a sales menu

    // vector<Stock> &getStock() const;
    // vector<CartItem> &getCart() const;
    // vector<CartItem> &getShelf() const;
    // vector<Client> &getClients() const;
    // array<SaleReport, 100> &getSales() const;

    // Stock Management
    Stock *findStockById( int stockId);
    Stock *findStockByName( const string &name);
    vector<Stock> searchForProduct(const string &name);
    void changeQuantityFromStock( Stock *item, int quantity);
    void changePurchaseFromStock( Stock *olditem, Stock newitem);
    void removePurchaseFromStock( Stock *item);
    void printStock(const string &title, vector<int> *idColor = nullptr, const string colorCode = "");
    void printProducts();

    // Cart Management
    CartItem *findItemCart(int id, int *index = nullptr);
    void addProductCart(bool menuState);
    void removeProductCart(bool menuState);
    void changeProductCart(bool menuState);
    void clearCart(vector<Stock> *shelf = nullptr); // check implementation
    void printCart();

    // Client Management
    Client *findClientById(int clientId);
    Client *findClientByName(const string &name);
    void addClient();
    void removeClient();
    void printClients();

    // Sales Management
    void checkoutMenu();
    double calculateCartTotal();
    Client *handleClientSelection();
    Client *createNewClient();
    double processPayment(double total);
    void completeCheckout(Client *client, double payment, double total);
    void gambling(vector<CartItem> &sale, int chance = 50);
};
