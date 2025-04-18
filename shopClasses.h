#include <iostream>
#include <string>  // for string
#include <ctime> // for time
#include <sstream> // for stringstream
#include <iomanip> // for setw
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
    string date;

    Receipt()
    {
        date = getCurrentDateTime();
    }

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

private:
string getCurrentDateTime() // for example: "2025-04-18 14:32"
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