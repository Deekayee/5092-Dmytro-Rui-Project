#include <iostream>
using namespace std;

class Stock
{
public:
    int stockId;
    int quantity;
    double costWithoutTax;
    string productName;

    double getCostWithTax(double taxRatePercent) const
    {
        return costWithoutTax * (1 + taxRatePercent / 100.0);
    }
};

class Receipt
{
public:
    int receiptId;
    int clientId;
    string productName;
    int quantity;
    double costWithoutTax;
    double taxRatePercent;
    double paymentAmount;

    double getCostWithTax() const
    {
        return costWithoutTax * (1 + taxRatePercent / 100.0);
    }

    double getTotalCost() const
    {
        return getCostWithTax() * quantity;
    }

    double getChange() const
    {
        return paymentAmount - getTotalCost();
    }
};
