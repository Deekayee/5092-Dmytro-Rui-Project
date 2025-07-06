#pragma once

#include <string>
#include <vector>

#include "cartItem.h"
#include "utils.h"

using namespace std;

// Forward declaration to minimize dependencies
//class CartItem;

class Receipt
{
private:
    static int nextReceiptId;

    // Constants for better maintainability
    static const double TAX_RATE;
    static const int DISPLAY_WIDTH = 81;

    int receiptId;
    int clientId;
    double paymentAmount;
    string date;
    vector<CartItem> items;

    // Private helper methods
    string getCurrentDateTime() const;
    double roundToTwoDecimals(double value) const;

public:
    // Constructors
    Receipt();
    Receipt(const vector<CartItem> &cart, double payment, int clientId);

    // Getters
    int getReceiptId() const;
    int getClientId() const;
    double getPaymentAmount() const;
    const string &getDate() const;
    const vector<CartItem> &getItems() const;
    double getTotalCostWithoutTax() const;
    double getTotalCost() const;
    double getTotalTax() const;
    double getChange() const;

    // Setters
    void addItem(const CartItem &item);
    void setClientId(int id);

    // Utility methods
    string toDisplay() const;
    string toString() const;
    void fromString(const string &line);

    // Static utilities
    static int getNextReceiptId();
    static void setNextReceiptId(int id);
};