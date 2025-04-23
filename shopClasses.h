#include <iostream>
#include <string>  // for string
#include <ctime>   // for time
#include <sstream> // for stringstream
#include <iomanip> // for setw
#include <vector>  // for vectors
using namespace std;

class Stock
{
public:
    int stockId;
    int quantity;
    double costValue;
    string productName;

    double getSaleValue() const
    {
        return costValue * 1.3;
    }
};

class CartItem
{
public:
    int stockId;
    int quantity;
    double costWithoutTax;
    double taxRatePercent;
    string productName;

    double getCostWithTax() const
    {
        return costWithoutTax * (1 + taxRatePercent / 100.0);
    }

    double getTotalCost() const
    {
        return getCostWithTax() * quantity;
    }
};

class Receipt
{
public:
    int receiptId;
    int clientId;
    double paymentAmount;
    string date;
    vector<CartItem> items;

    Receipt()
    {
        date = getCurrentDateTime();
    }

    void addItem(const CartItem &item)
    {
        items.push_back(item);
    }

    double getTotalCost() const
    {
        double total = 0;
        for (const auto &item : items)
        {
            total += item.getTotalCost();
        }
        return total;
    }

    double getChange() const
    {
        return paymentAmount - getTotalCost();
    }

private:
    string getCurrentDateTime()
    {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
           << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
           << setfill('0') << setw(2) << ltm->tm_mday << " "
           << setfill('0') << setw(2) << ltm->tm_hour << ":"
           << setfill('0') << setw(2) << ltm->tm_min;
        return ss.str();
    }
};