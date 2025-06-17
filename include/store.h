#pragma once

#include <string>
#include <vector>
#include <array>

#include "../include/stock.h"
#include "../include/cartItem.h"
#include "../include/client.h"
#include "../include/receipt.h"

using namespace std;
// ideas:
// - static class, with high level functionality
// - manage menu states
// - initialize daughter classes

class Store
{
private:
    vector <Stock> stockList;
    vector <CartItem> cart;
    vector <Client> clientList;
    array <Receipt, 100> saleList;

public:
    // tbd
    // Constructors
    Store(string stockFile, string clientFile, string saleFile);

    // Getters
    vector <Stock>& stockList();
    vector <CartItem>& cart();
    vector <Client>& clientList();
    array <Receipt, 100> saleList();


    // Setters
    // Do we even need them?

    // Methods
    // Need print methods for all vectors
};