#pragma once

#include "saleReport.h"
#include "client.h"
#include "Stock.h"

#include <string>
#include <array>
#include <vector>

class product;
class sale;

class Report
{
    int stockIds;
    int stockTotal;
    array<SaleReport, 100> sales;
    double getTotalProfit(int id);
    int getTotalQuantity(int id);

public:
    int getTopSeller(int &totalProfit); // with combined profits
    int getWorstSeller();
    Client getBestClient();

    void addSale();
};
