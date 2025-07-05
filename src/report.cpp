#include "../include/report.h"

using namespace std;

double Report::getTotalProfit(int id)
{
    double totalProfit = 0;
    for (int i = 0; i < 100; i++)
    {
        ProductReport *tmp = sales.at(i).findProductId(id);
        if (tmp != nullptr)
            totalProfit += tmp->getSaleProfit();
    }
    return totalProfit;
}

int Report::getTotalQuantity(int id)
{
    int totalQuantity = 0;
    for (int i = 0; i < 100; i++)
    {
        ProductReport *tmp = sales.at(i).findProductId(id);
        if (tmp != nullptr)
            totalQuantity += tmp->getQuantity();
    }
    return totalQuantity;
}

int Report::getTopSeller(int &topSellerProfit)
{
    int topSellerId;
    int topSellerQtty = 0;

    for (int i = 0; i < stockIds; i++)
    {
        if (topSellerQtty < getTotalQuantity(i))
        {
            topSellerId = i;
            topSellerQtty = getTotalQuantity(i);
        }
    }
    topSellerProfit = getTotalProfit(topSellerId);
    return topSellerId;
}

int Report::getWorstSeller()
{
    int worstSellerId;
    int worstSellerQtty;

    for (int i = 0; i < stockIds; i++)
    {
        if (worstSellerQtty > getTotalQuantity(i))
        {
            worstSellerId = i;
            worstSellerQtty = getTotalQuantity(i);
        }
    }
}

Client Report::getBestClient()
{
}

void Report::addSale()
{
}