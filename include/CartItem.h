#pragma once
#include "../include/Stock.h"

#include <iostream> // for cout
#include <string>   // for string
#include <ctime>    // for time
#include <sstream>  // for stringstream
#include <iomanip>  // for setw
#include <vector>   // for vectors
#include <cmath>    // for rounding doubles



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
    CartItem();

    // Construct a CartItem from a Stock item, quantity and tax rate (default = 23%)
    CartItem(const Stock &stock, int qty, double taxRate = 23.0);

    int getStockId() const;
    int getQuantity() const;
    double getSaleWithoutTax() const;
    double getTaxRatePercent() const;
    string getProductName() const;

    void setStockId(int id);
    void setQuantity(int qty);
    void setSaleWithoutTax(double price);
    void setTaxRatePercent(double rate);
    void setProductName(string name);

    // Calculates and returns the sale value of the item including tax by applying the tax rate to the sale value without tax.
    double getSaleWithTax() const;

    // Returns the total value of the item in the cart, without tax.
    double getTotalSaleWithoutTax() const;

    // Returns the total value of the item in the cart, including tax.
    double getTotalItemSellValue() const;

    // Returns a string with the CartItem attributes in CSV format.
    string toString() const;

    string toDisplay() const;

    // Parses a comma-separated string to initialize CartItem attributes.
    void fromString(string line);
};