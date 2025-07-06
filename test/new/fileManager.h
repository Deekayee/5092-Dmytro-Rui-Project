#pragma once

#include <string>
#include <vector>
#include "stock.h"
#include "client.h"
#include "receipt.h"
#include "cartItem.h"

using namespace std;

class FileManager
{
public:
    static bool loadStock(vector<Stock> &stockList);
    static bool saveStock(const vector<Stock> &stockList);
    static bool loadClients(vector<Client> &clientList);
    static bool saveClients(const vector<Client> &clientList);
    static bool loadReceipts(array<Receipt,100> &saleList);
    static bool saveReceipts(const array<Receipt,100> &saleList);
};