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

    // Stock Management
    Stock* findStockById(vector<Stock>& stockList, int stockId);
    Stock* findStockByName(vector<Stock>& stockList, const string& name);
    vector<Stock> searchProducts(const string& name);
    void updateStockQuantity(int stockId, int newQuantity);
    void removeFromStock(int stockId, int quantity);

    // Cart Management
    void addToCart(int stockId, int quantity);
    void removeFromCart(int stockId);
    void clearCart();
    CartItem* findInCart(int stockId);

    // Client Management
    Client* findClientById(vector<Client>& clientList, int clientId);
    Client* findClientByName(vector<Client>& clientList, const string& name);

    // Sales Management
    void processCheckout();
    void generateReceipt();
};