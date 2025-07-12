#include "cartItem.h"
#include <string>

// Constructors
CartItem::CartItem() : stockId(0), quantity(0), saleWithoutTax(0.0), taxRatePercent(0.0), productName("") {}
CartItem::CartItem(const Stock &stock, int qty, double taxRate)
{
    stockId = stock.getStockId();
    productName = stock.getProductName();
    quantity = qty;
    taxRatePercent = taxRate;
    saleWithoutTax = stock.getSaleValue();
}

// Getters
int CartItem::getQuantity() const { return quantity; }
int CartItem::getStockId() const { return stockId; }
double CartItem::getSaleWithoutTax() const { return saleWithoutTax; }
double CartItem::getTaxRatePercent() const { return taxRatePercent; }
const string &CartItem::getProductName() const { return productName; }
double CartItem::getSaleWithTax() const
{
    return saleWithoutTax * (1 + taxRatePercent / 100.0);
}
double CartItem::getTotalSaleWithoutTax() const
{
    return saleWithoutTax * quantity;
}
double CartItem::getTotalItemSellValue() const
{
    return getSaleWithTax() * quantity;
}

// Setters
void CartItem::setStockId(int id) { stockId = id; }
void CartItem::setQuantity(int qty) { quantity = qty; }
void CartItem::setSaleWithoutTax(double price) { saleWithoutTax = price; }
void CartItem::setTaxRatePercent(double rate) { taxRatePercent = rate; }
void CartItem::setProductName(string &name) { productName = name; }

// Methods
string CartItem::toString() const
{
    stringstream ss;
    ss << stockId << ','
       << productName << ','
       << quantity << ','
       << fixed << setprecision(2) << saleWithoutTax << ','
       << fixed << setprecision(2) << taxRatePercent;
    return ss.str();
}

// Method for displaing data
string CartItem::toDisplay() const
{
    stringstream ss;
    ss << setw(2) << stockId << " | "
       << setw(22) << left << productName << " | "
       << setw(5) << right << quantity << " | "
       << setw(8) << right << fixed << setprecision(2) << getSaleWithTax() << " eur | "
       << setw(9) << right << fixed << setprecision(2) << getTotalItemSellValue() << " eur";

    return ss.str();
}

// Method for displaing data overload
string CartItem::toDisplay(int receiptOrder) const
{
    stringstream ss;
    ss << setw(2) << receiptOrder << " | "
       << setw(22) << left << productName << " | "
       << setw(5) << right << quantity << " | "
       << setw(8) << right << fixed << setprecision(2) << getSaleWithTax() << " eur | "
       << setw(9) << right << fixed << setprecision(2) << getTotalItemSellValue() << " eur";

    return ss.str();
}

// Method for reading data
void CartItem::fromString(const string &line)
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
    getline(ss, field);
    taxRatePercent = stod(field);
}
