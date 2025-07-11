#pragma once

#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

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
    // Constructors
    Stock();
    Stock(const string &name, int qty, double price);

    // Getters
    int getStockId() const;
    int getQuantity() const;
    double getCostValue() const;
    const string &getProductName() const;
    double getSaleValue() const;

    // Static getters
    static int getNextStockId();

    // Setters
    void setStockId(int id);
    void setQuantity(int qty);
    void setCostValue(double price);
    void setProductName(const string &name);
    static void setNextStockId(int id);
    static void incrementStockId();

    // Methods
    string toString() const;
    string toDisplay() const;
    void fromString(const string &line);
};