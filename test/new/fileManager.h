#pragma once

#include <string>
#include <vector>
#include "stock.h"
#include "client.h"
#include "saleReport.h"

using namespace std;

class FileManager
{
public:
    static bool loadStock(vector<Stock> &stockList);
    static bool saveStock(const vector<Stock> &stockList);
    static bool loadClients(vector<Client> &clientList);
    static bool saveClients(const vector<Client> &clientList);
    static bool loadSales(array<SaleReport,100> &saleList);
    static bool saveSales(const array<SaleReport,100> &saleList);
};