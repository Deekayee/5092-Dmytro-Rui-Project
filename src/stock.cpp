#include "../include/stock.h"


// Static member initialization
int Stock::nextStockId = 1;

// Default constructor for Stock.
Stock::Stock() : quantity(0), costValue(0.0), productName(""), stockId(0) {}

// Construct a Stock object with a given name, quantity and price.
Stock::Stock(const string &name, int qty, double price)
{
    stockId = nextStockId++;
    productName = name;
    quantity = qty;
    costValue = round(price * 100.0) / 100.0;
}

// Getters
int Stock::getStockId() const { return stockId; }
int Stock::getQuantity() const { return quantity; }
double Stock::getCostValue() const { return costValue; }
const string& Stock::getProductName() const { return productName; }
double Stock::getSaleValue() const
{
    const double saleRate = 0.3;
    return costValue * (1 + saleRate);
}

// Setters
void Stock::setStockId(int id) { stockId = id; }
void Stock::setQuantity(int qty) { quantity = qty; }
void Stock::setCostValue(double price) { costValue = price; }
void Stock::setProductName(string& name) { productName = name; }

// Static methods
int Stock::getNextStockId() { return nextStockId; }
void Stock::incrementStockId() { ++nextStockId; }
void Stock::setNextStockId(int id) { nextStockId = id; }

// Utility methods

// Returns a string representation of the Stock object in CSV format.
string Stock::toString() const
{
    stringstream ss;
    
    ss << stockId << ',' << productName << ',' << quantity << ',' << fixed << setprecision(2) << costValue;
    return ss.str();
}

// Returns a string representation of the Stock object in a display-friendly
// format, with left-aligned product name and right-aligned quantity and price.
string Stock::toDisplay() const
{
    stringstream ss;

    ss << setw(2) << stockId << " | "
       << setw(22) << left << productName << " | "
       << setw(8) << right << quantity << " | "
       << fixed << setprecision(2) << costValue << " eur";
    return ss.str();
}

// Parses a comma-separated string to initialize Stock attributes: stockId,
// productName, quantity, and costValue.
void Stock::fromString(const string& line)
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
