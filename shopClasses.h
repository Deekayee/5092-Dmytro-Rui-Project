#pragma once //  compiler only sees this lib file once

#include <iostream> // for cout
#include <string>   // for string
#include <ctime>    // for time
#include <sstream>  // for stringstream
#include <iomanip>  // for setw
#include <vector>   // for vectors
#include <cmath>    // for rounding doubles
using namespace std;

class Stock
{
private:
    static int nextStockId;

    int stockId;
    int quantity;
    double costValue;
    string productName;

public:
    // Default constructor for Stock. Initializes stockId to the next available ID, and all other fields to zero/default values.
    Stock() : quantity(0), costValue(0.0), productName(""), stockId(0) {} // temporary invalid id

    // Construct a Stock object with a given name, quantity and price.
    Stock(string name, int qty, double price)
    {
        stockId = nextStockId++;
        productName = name;
        quantity = qty;
        costValue = round(price * 100.0) / 100.0;
    }

    int getStockId() const { return stockId; }
    int getQuantity() const { return quantity; }
    double getCostValue() const { return costValue; }
    string getProductName() const { return productName; }
    static int getNextStockId() { return nextStockId; }
    static void incrementStockId() { ++nextStockId; }
    static void setNextStockId(int id) { nextStockId = id; }

    // Returns a string representation of the Stock object in CSV format.
    string toString()
    {
        stringstream ss;
        ss << stockId << ',' << productName << ',' << quantity << ',' << fixed << setprecision(2) << costValue;
        return ss.str();
    }

    // Returns a string representation of the Stock object in a display-friendly format, with left-aligned product name and right-aligned quantity and price.
    string toDisplay() const
    {
        stringstream ss;
        ss << setw(2) << stockId << " | "
           << setw(22) << left << productName << " | "
           << setw(8) << right << quantity << " | "
           << fixed << setprecision(2) << costValue << " eur";
        return ss.str();
    }

    // Returns the sale value of the item, which is the cost value plus 30% sales markup.
    double getSaleValue() const
    {
        const double saleRate = 0.3;
        return costValue * (1 + saleRate);
    }

    void setStockId(int id) { stockId = id; }
    void setQuantity(int qty) { quantity = qty; }
    void setCostValue(double price) { costValue = price; }
    void setProductName(string name) { productName = name; }

    // Parses a comma-separated string to initialize Stock attributes: stockId, productName, quantity, and costValue.
    void fromString(string line)
    {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        stockId = stoi(field);
        getline(ss, productName, ',');
        getline(ss, field, ',');
        quantity = stoi(field);
        getline(ss, field);
        costValue = stod(field);
    }
};

class CartItem
{
private:
    int stockId;
    int quantity;
    double saleWithoutTax;
    double taxRatePercent;
    string productName;

public:
    // Default constructor
    CartItem() : stockId(0), quantity(0), saleWithoutTax(0.0), taxRatePercent(0.0), productName("") {}

    // Construct a CartItem from a Stock item, quantity and tax rate (default = 23%)
    CartItem(const Stock &stock, int qty, double taxRate = 23.0)
    {
        stockId = stock.getStockId();
        productName = stock.getProductName();
        quantity = qty;
        taxRatePercent = taxRate;
        saleWithoutTax = stock.getSaleValue();
    }

    int getStockId() const { return stockId; }
    int getQuantity() const { return quantity; }
    int getSaleWithoutTax() const { return saleWithoutTax; }
    double getTaxRatePercent() const { return taxRatePercent; }
    string getProductName() const { return productName; }

    void setStockId(int id) { stockId = id; }
    void setQuantity(int qty) { quantity = qty; }
    void setSaleWithoutTax(double price) { saleWithoutTax = price; }
    void setTaxRatePercent(double rate) { taxRatePercent = rate; }
    void setProductName(string name) { productName = name; }

    // Calculates and returns the sale value of the item including tax by applying the tax rate to the sale value without tax.
    double getSaleWithTax() const
    {
        return saleWithoutTax * (1 + taxRatePercent / 100.0);
    }

    // Returns the total value of the item in the cart, without tax.
    double getTotalSaleWithoutTax() const
    {
        return saleWithoutTax * quantity;
    }

    // Returns the total value of the item in the cart, including tax.
    double getTotalItemSellValue() const
    {
        return getSaleWithTax() * quantity;
    }

    // Returns a string with the CartItem attributes in CSV format.
    string toString() const
    {
        stringstream ss;
        ss << stockId << ',' << productName << ',' << quantity << ',' << fixed << setprecision(2) << saleWithoutTax << ',' << fixed << setprecision(2) << taxRatePercent << ',' << fixed << setprecision(2) << getSaleWithTax() << ',' << fixed << setprecision(2) << getTotalItemSellValue();
        return ss.str();
    }

    string toDisplay() const
    {
        stringstream ss;
        ss << setw(2) << stockId << " | "
           << setw(22) << left << productName << " | "
           << setw(5) << right << quantity << " | "
           << setw(8) << right << fixed << setprecision(2) << getSaleWithTax() << " eur | "
           << setw(9) << right << fixed << setprecision(2) << getTotalItemSellValue() << " eur";

        return ss.str();
    }

    // Parses a comma-separated string to initialize CartItem attributes.
    void fromString(string line)
    {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        stockId = stoi(field);
        getline(ss, productName, ',');
        getline(ss, field, ',');
        quantity = stoi(field);
        getline(ss, field, ',');
        saleWithoutTax = stod(field);
        getline(ss, field, ',');
        taxRatePercent = stod(field);
        getline(ss, field, ',');
        double saleWithTax = stod(field);
        getline(ss, field);
        double totalItemSellValue = stod(field);
    }
};

class Receipt
{
private:
    static int nextReceiptId;
    static int nextClientId;

    int receiptId;
    int clientId;
    double paymentAmount;
    string date;
    vector<CartItem> items;

public:
    int getReceiptId() const { return receiptId; }
    int getClientId() const { return clientId; }
    double getPaymentAmount() const { return paymentAmount; }
    string getDate() const { return date; }
    vector<CartItem> getItems() const { return items; }

    // Initializes a Receipt object with a unique receipt ID, client ID, current date, and default payment amount.
    Receipt() : paymentAmount(0.0)
    {
        receiptId = nextReceiptId++;
        clientId = nextClientId++;
        date = getCurrentDateTime();
    }

    // new constructor to auto-create Receipt from a cart
    Receipt(const vector<CartItem> &cart, double payment)
    {
        receiptId = nextReceiptId++;
        clientId = nextClientId++;
        paymentAmount = payment;
        date = getCurrentDateTime();
        items = cart; // simple copy of all cart items
    }

    // Adds a CartItem to the receipt.
    void addItem(const CartItem &item)
    {
        items.push_back(item);
    }

    double getTotalCostWithoutTax() const
    {
        double total = 0;
        for (const auto &item : items)
        {
            total += item.getTotalSaleWithoutTax();
        }
        total = round(total) / 100;
        return total;
    }

    // Calculates the total cost of all items in the receipt by summing the total value of each item, including tax.
    double getTotalCost() const
    {
        double total = 0;
        for (const auto &item : items)
        {
            total += item.getTotalItemSellValue();
        }
        total = round(total * 100) / 100;
        return total;
    }

    // Calculates the total tax amount of all items in the receipt by summing the tax amount of each item.
    double getTotalTax() const
    {
        double total = 0;
        for (const auto &item : items)
        {
            total += item.getTotalItemSellValue() - item.getTotalSaleWithoutTax();
        }
        total = round(total * 100) / 100;
        return total;
    }

    // Calculates the change to be returned to the client based on the total cost of the items purchased.
    double getChange() const
    {
        double change = round((paymentAmount - getTotalCost()) * 100) / 100;
        return change;
    }

    // Returns a string representation of the receipt, including its ID, client ID, payment amount, date, items and total cost and change.
    string toDisplay() const
    {
        stringstream ss;
        ss << "Receipt:" << endl;
        ss << string(81, '-') << endl;
        ss << "Receipt ID: " << receiptId << endl;
        ss << "Client ID:  " << clientId << endl;
        ss << "Date:       " << date << endl;
        ss << "Items:" << endl;

        ss << string(81, '-') << endl;

        // Table header
        ss << setw(2) << "ID" << " | "
           << setw(22) << left << "Product Name" << " | "
           << setw(5) << right << "Qtty" << " | "
           << setw(12) << right << "Price" << " | "
           << setw(12) << right << "Total"
           << endl;

        ss << string(81, '-') << endl;

        // Items
        for (const auto &item : items)
        {
            ss << item.toDisplay() << endl;
        }

        ss << string(81, '-') << endl;

        // Totals
        ss << setw(25) << right << "Total w/o Tax: "
           << setw(9) << fixed << setprecision(2) << getTotalCostWithoutTax() << " eur" << endl;

        ss << setw(25) << right << "Total Tax (23%): "
           << setw(9) << fixed << setprecision(2) << getTotalTax() << " eur" << endl;

        ss << setw(25) << right << "Total Cost: "
           << setw(9) << fixed << setprecision(2) << getTotalCost() << " eur" << endl;

        ss << setw(25) << right << "Payment Amount: "
           << setw(9) << fixed << setprecision(2) << paymentAmount << " eur" << endl;

        ss << setw(25) << right << "Change: "
           << setw(9) << fixed << setprecision(2) << getChange() << " eur" << endl;

        ss << string(81, '-') << endl
           << endl;

        return ss.str();
    }

    // Parses a comma-separated string to initialize Receipt attributes and CartItems.
    void fromString(string line)
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

private:
    // Returns a string with the current date and time in the format "YYYY-MM-DD HH:MM".
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
