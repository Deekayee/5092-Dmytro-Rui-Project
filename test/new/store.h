#pragma once

#include <vector>
#include <array>

#include "menu.h"
#include "stock.h"
#include "cartItem.h"
#include "client.h"
#include "saleReport.h"
#include "fileManager.h"

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

    vector<Stock> &getStock() const;
    vector<CartItem> &getCart() const;
    vector<CartItem> &getShelf() const;
    vector<Client> &getClients() const;
    array<SaleReport, 100> &getSales() const;
};
