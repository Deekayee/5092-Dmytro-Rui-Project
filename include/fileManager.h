#pragma once

#include <string>
#include <vector>
#include "stock.h"
#include "client.h"

using namespace std;

class FileManager
{
public:
    static bool loadStockFromFile(const string &filename, vector<Stock> &stockList);
    static bool saveStockToFile(const string &filename, const vector<Stock> &stockList);
    static bool loadClientsFromFile(const string &filename, vector<Client> &clientList);
    static bool saveClientsToFile(const string &filename, const vector<Client> &clientList);
};