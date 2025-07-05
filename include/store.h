#pragma once

#include <string>
#include <vector>
#include <array>

#include "../include/stock.h"
#include "../include/cartItem.h"
#include "../include/client.h"
#include "../include/receipt.h"
#include "../include/fileManager.h"

using namespace std;
// ideas:
// - static class, with high level functionality
// - manage menu states
// - initialize daughter classes

class Store
{
private:
    vector<Stock> stockList;
    vector<CartItem> cart;
    vector<Stock> shelf; // WARNING: implies a lot of fixing, but I think it's better to have this here instead of passing it as argument everywhere, TODO: fix functions that accept it as argument
    vector<Client> clientList;
    array<Receipt, 100> saleList;

public:
    // Constructors
    Store();

    // Getters
    vector<Stock> &getStockList();
    vector<CartItem> &getCart();
    vector<Client> &getClientList();
    array<Receipt, 100> getSaleList();

    // Methods
    // Data Management
    bool initializeData();
    void shelfInit(vector<Stock> &stockList, vector<CartItem> &cart, vector<Stock> &shelf);
    void updateStockFromShelf(vector<Stock> &stockList, vector<Stock> &shelf);

    // Stock Management
    Stock *findStockById(vector<Stock> &stockList, int stockId);
    Stock *findStockByName(vector<Stock> &stockList, const string &name);
    vector<Stock> searchForProduct(const string &name);
    void changeQuantityFromStock(vector<Stock> &stockList, Stock *item, int quantity);
    void changePurchaseFromStock(vector<Stock> &stockList, Stock *olditem, Stock newitem);
    void removePurchaseFromStock(vector<Stock> &stockList, Stock *item);
    void printStock(const vector<Stock> &stockList, const string &title, vector<int> *idColor = nullptr, const string colorCode = "");
    void printProducts(const vector<Stock> &shelf);

    // Cart Management
    CartItem *findItemCart(vector<CartItem> &cart, int id, int *index = nullptr);
    void addProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
    void removeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
    void changeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
    void clearCart(vector<CartItem> &cart, vector<Stock> *shelf = nullptr);
    void printCart(vector<CartItem> &cart);

    // Client Management
    Client *findClientById(vector<Client> &clientList, int clientId);
    Client *findClientByName(vector<Client> &clientList, const string &name);
    void addClient(vector<Client> &clientList);
    void removeClient(vector<Client> &clientList);
    void printClients(const vector<Client> &clientList);

    // Sales Management
    void checkoutMenu();
    double calculateCartTotal();
    Client *handleClientSelection();
    Client *createNewClient();
    double processPayment(double total);
    void completeCheckout(Client *client, double payment, double total);
    void gambling(vector<CartItem> &sale, int chance = 50);
};