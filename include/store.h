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
    Store(const string &stockFile, const string &clientFile, const string &saleFile);

    // Getters
    vector<Stock> &getStockList();
    vector<CartItem> &getCart();
    vector<Client> &getClientList();
    array<Receipt, 100> getSaleList();

    // Setters
    // Do we even need them? I guess not

    // Methods
};