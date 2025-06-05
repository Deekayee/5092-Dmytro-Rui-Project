#pragma once

#include <string>
#include "stock.h"

class CartItem
{
private:
    int stockId;
    int quantity;
    double saleWithoutTax;
    double taxRatePercent;
    string productName;

public:
    // Constructors
    CartItem();
    CartItem(const Stock &stock, int qty, double taxRate = 23.0);

    // Getters
    const int getStockId();
    const int getQuantity();
    const double getSaleWithoutTax();
    const double getTaxRatePercent();
    const string &getProductName();
    const double getSaleWithTax();
    const double getTotalSaleWithoutTax();
    const double getTotalItemSellValue();

    // Setters
    void setStockId(int id);
    void setQuantity(int qty);
    void setSaleWithoutTax(double price);
    void setTaxRatePercent(double rate);
    void setProductName(string &name);

    // Methods
    string toString() const;
    string toDisplay() const;
    void fromString(const string &line);
};