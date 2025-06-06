#pragma once

#include "../include/stock.h"

using namespace std;
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
    int getQuantity() const;
    int getStockId() const;
    double getSaleWithoutTax() const;
    double getTaxRatePercent() const;
    const string &getProductName() const;
    double getSaleWithTax() const;
    double getTotalSaleWithoutTax() const;
    double getTotalItemSellValue() const;

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