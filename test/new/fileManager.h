#pragma once

#include <string>
#include <vector>
#include "stock.h"
#include "client.h"
#include "receipt.h"

using namespace std;

class FileManager
{
public:
    static void loadStock(vector<Stock> &stockList);
    static bool saveStock(const vector<Stock> &stockList);
    static void loadClients(vector<Client> &clientList);
    static bool saveClients(const vector<Client> &clientList);
    static void loadReceipts(array<Receipt, 100> &saleList);
    static bool saveReceipts(const array<Receipt, 100> &saleList);
};