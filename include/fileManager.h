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
    static bool loadStockFromFile(const string &filename, vector<Stock> &stockList);
    static bool saveStockToFile(const string &filename, const vector<Stock> &stockList);
    static bool loadClientsFromFile(const string &filename, vector<Client> &clientList);
    static bool saveClientsToFile(const string &filename, const vector<Client> &clientList);
    static bool loadReceiptsFromFile(const string &filename, array<Receipt,100> &saleList);
    static bool saveReceiptsToFile(const string &filename, const array<Receipt,100> &saleList);
};