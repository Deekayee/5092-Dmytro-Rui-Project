#include "receipt.h"
#include "cartItem.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>

// Static member initialization
int Receipt::nextReceiptId = 1;

// Default constructor
Receipt::Receipt() : receiptId(nextReceiptId++), clientId(0), paymentAmount(0.0), date(getCurrentDateTime()) {}

// Constructor with cart and payment
Receipt::Receipt(const vector<CartItem> &cart, double payment, int clntId)
{
    receiptId = nextReceiptId++;
    clientId = clntId;
    paymentAmount = payment;
    date = getCurrentDateTime();
    items = cart;
}

// Getters
int Receipt::getReceiptId() const
{
    return receiptId;
}

int Receipt::getClientId() const
{
    return clientId;
}

double Receipt::getPaymentAmount() const
{
    return paymentAmount;
}

const string &Receipt::getDate() const
{
    return date;
}

const vector<CartItem> &Receipt::getItems() const
{
    return items;
}

// Business logic methods
void Receipt::addItem(const CartItem &item)
{
    items.push_back(item);
}

double Receipt::getTotalCostWithoutTax() const
{
    double total = 0.0;
    for (const auto &item : items)
    {
        total += item.getTotalSaleWithoutTax();
    }
    return roundToTwoDecimals(total);
}

double Receipt::getTotalCost() const
{
    double total = 0.0;
    for (const auto &item : items)
    {
        total += item.getTotalItemSellValue();
    }
    return roundToTwoDecimals(total);
}

double Receipt::getTotalTax() const
{
    return roundToTwoDecimals(getTotalCost() - getTotalCostWithoutTax());
}

double Receipt::getChange() const
{
    return roundToTwoDecimals(paymentAmount - getTotalCost());
}

// Display method
string Receipt::toDisplay() const
{
    stringstream ss;

    // Header
    ss << "Receipt:\n";
    ss << string(DISPLAY_WIDTH, '-') << '\n';
    ss << "Receipt ID: " << receiptId << '\n';
    ss << "Client ID:  " << clientId << '\n';
    ss << "Date:       " << date << '\n';
    ss << "Items:\n";
    ss << string(DISPLAY_WIDTH, '-') << '\n';

    // Table header
    ss << setw(2) << "ID" << " | "
       << setw(22) << left << "Product Name" << " | "
       << setw(5) << right << "Qtty" << " | "
       << setw(12) << right << "Price" << " | "
       << setw(12) << right << "Total" << '\n';

    ss << string(DISPLAY_WIDTH, '-') << '\n';

    // Items
    for (const auto &item : items)
    {
        ss << item.toDisplay() << '\n';
    }

    ss << string(DISPLAY_WIDTH, '-') << '\n';

    // Totals with consistent formatting
    const int labelWidth = 25;
    const int valueWidth = 9;

    ss << setw(labelWidth) << right << "Total w/o Tax: "
       << setw(valueWidth) << fixed << setprecision(2)
       << getTotalCostWithoutTax() << " eur\n";

    ss << setw(labelWidth) << right << "Total Tax ("
       << fixed << setprecision(0) << (TAX_RATE * 100) << "%): "
       << setw(valueWidth) << fixed << setprecision(2)
       << getTotalTax() << " eur\n";

    ss << setw(labelWidth) << right << "Total Cost: "
       << setw(valueWidth) << fixed << setprecision(2)
       << getTotalCost() << " eur\n";

    ss << setw(labelWidth) << right << "Payment Amount: "
       << setw(valueWidth) << fixed << setprecision(2)
       << paymentAmount << " eur\n";

    ss << setw(labelWidth) << right << "Change: "
       << setw(valueWidth) << fixed << setprecision(2)
       << getChange() << " eur\n";

    ss << string(DISPLAY_WIDTH, '-') << "\n\n";

    return ss.str();
}

string Receipt::toString() const
{
    string str;
    str = to_string(receiptId) + "," + to_string(clientId) + "," + to_string(paymentAmount);
}

// Parser
void Receipt::fromString(const string &line)
{
    stringstream ss(line);
    string field;
    getline(ss, field, ',');
    receiptId = stoi(field);
    getline(ss, field, ',');
    clientId = stoi(field);
    getline(ss, field, ',');
    paymentAmount = stod(field);
    getline(ss, date, ',');
    while (getline(ss, field, ','))
    {
        CartItem item;
        item.fromString(field);
        items.push_back(item);
    }
}

// Static methods
int Receipt::getNextReceiptId()
{
    return nextReceiptId;
}

void Receipt::setNextReceiptId(int id)
{
    if (id > 0)
    {
        nextReceiptId = id;
    }
}

// Private helper methods
string Receipt::getCurrentDateTime() const
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-"
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min;

    return ss.str();
}

double Receipt::roundToTwoDecimals(double value) const
{
    return round(value * 100.0) / 100.0;
}