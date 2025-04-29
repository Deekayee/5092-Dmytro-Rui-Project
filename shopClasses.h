#pragma once //  compiler only sees this lib file once
#include <iostream>
#include <string>  // for string
#include <ctime>   // for time
#include <sstream> // for stringstream
#include <iomanip> // for setw
#include <vector>  // for vectors
#include <cmath>   // for rounding doubles
using namespace std;

class Stock
{
private: // private this and do gets and sets, do a to_string
    static int nextStockId;

    int stockId;
    int quantity;
    double costValue;
    string productName;

public:
    Stock() : quantity(0), costValue(0.0), productName("")
    {
        stockId = nextStockId++;
    }

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

    string toString()
    {
        stringstream ss;
        ss << stockId << ',' << productName << ',' << quantity << ',' << fixed << setprecision(2) << costValue;
        return ss.str();
    }

    double getSaleValue() const
    {
        const double taxRate = 0.3;
        return costValue * (1 + taxRate);
    }

    void setStockId(int id) { stockId = id; }
    void setQuantity(int qty) { quantity = qty; }
    void setCostValue(double price) { costValue = price; }
    void setProductName(string name) { productName = name; }

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
    CartItem() : stockId(0), quantity(0), saleWithoutTax(0.0), taxRatePercent(0.0), productName("") {}

    CartItem(const Stock &stock, int qty, double taxRate = 23.0) // default tax is 23%
    {
        stockId = stock.getStockId();
        productName = stock.getProductName();
        quantity = qty;
        taxRatePercent = taxRate;
        saleWithoutTax = stock.getSaleValue(); // fetch from stock method
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

    double getSaleWithTax() const
    {
        return saleWithoutTax * (1 + taxRatePercent / 100.0);
    }

    double getTotalItemSellValue() const
    {
        return getSaleWithTax() * quantity;
    }

    string toString() const
    {
        stringstream ss;
        ss << stockId << ',' << productName << ',' << quantity << ',' << fixed << setprecision(2) << saleWithoutTax << ',' << fixed << setprecision(2) << taxRatePercent << ',' << fixed << setprecision(2) << getSaleWithTax() << ',' << fixed << setprecision(2) << getTotalItemSellValue();
        return ss.str();
    }

    // dont really need this yet
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

    Receipt() : paymentAmount(0.0)
    {
        receiptId = nextReceiptId++;
        clientId = nextClientId++;
        date = getCurrentDateTime();
    }

    // New constructor to auto-create Receipt from a cart
    Receipt(const vector<CartItem> &cart, double payment)
    {
        receiptId = nextReceiptId++;
        clientId = nextClientId++;
        paymentAmount = payment;
        date = getCurrentDateTime();
        items = cart; // simple copy of all cart items
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
            total += item.getTotalItemSellValue();
        }
        return total;
    }

    double getChange() const
    {
        return paymentAmount - getTotalCost();
    }

    string toString() const
    {
        stringstream ss;
        ss << "Receipt ID: " << receiptId << endl;
        ss << "Client ID: " << clientId << endl;
        ss << "Payment Amount: $" << fixed << setprecision(2) << paymentAmount << endl;
        ss << "Date: " << date << endl;
        ss << "Items:" << endl;
        for (auto &item : items)
        {
            ss << item.toString() << endl;
        }
        ss << "Total Cost: $" << fixed << setprecision(2) << getTotalCost() << endl;
        ss << "Change: $" << fixed << setprecision(2) << getChange() << endl;
        return ss.str();
    }

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

// init static variables
int Stock::nextStockId = 1;
int Receipt::nextReceiptId = 1;
int Receipt::nextClientId = 1;

// TODO
// Separate this into documentation file afterwards

/*
How this works:

Stock myCamera;
myCamera.stockId = 1;
myCamera.productName = "Sony A6000";
myCamera.quantity = 10;
myCamera.costValue = 500.0;

CartItem cartItem(myCamera, 2); // buying 2 units with 23% tax

cout << "Item total with tax: " << cartItem.getTotalItemSellValue() << endl;

-------------------------------------------------------------------------------------
for Receipt:

vector<CartItem> cart;
// Assume cart is filled with CartItem objects

double userPayment = 1300.0;
int newReceiptId = 1;
int newClientId = 1;

Receipt receipt(cart, userPayment, newReceiptId, newClientId);

cout << "Receipt total: " << receipt.getTotalCost() << endl;
cout << "Change to give: " << receipt.getChange() << endl;

-------------------------------------------------------------------------------------
Added autoincrementation

Stock camera;
camera.productName = "Canon M50";
camera.quantity = 5;
camera.costValue = 600.0;

CartItem item(camera, 2); // 2 units of this stock

vector<CartItem> cart = { item };

Receipt receipt(cart, 1500.0); // only need to pass cart and payment

cout << "Receipt ID: " << receipt.receiptId << ", Client ID: " << receipt.clientId << endl;

-------------------------------------------------------------------------------------
vector<Stock> inventory;

// Adding some stock entries
Stock cam1;
cam1.productName = "Canon M50";
cam1.quantity = 5;
cam1.costValue = 600.0;

Stock cam2;
cam2.productName = "Sony A6000";
cam2.quantity = 3;
cam2.costValue = 500.0;

inventory.push_back(cam1);
inventory.push_back(cam2);

// Display stock
for (const auto& item : inventory) {
    cout << "ID: " << item.stockId << ", Product: " << item.productName
         << ", Qty: " << item.quantity << ", Sale Value: " << item.getSaleValue() << endl;
}

*/