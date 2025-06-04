#pragma once
#include "../include/CartItem.h" // will hold the CartItem class

#include <iostream> // for cout
#include <string>   // for string
#include <ctime>    // for time
#include <sstream>  // for stringstream
#include <iomanip>  // for setw
#include <vector>   // for vectors
#include <cmath>    // for rounding doubles

using namespace std;

// Sale seems to have our receipt logic, thus is used
// prlly needs name changes, ie refactoring (f2)
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
    int getReceiptId() const;
    int getClientId() const;
    double getPaymentAmount() const;
    string getDate() const;
    vector<CartItem> getItems() const;

    // Initializes a Receipt object with a unique receipt ID, client ID, current date, and default payment amount.
    Receipt();

    // new constructor to auto-create Receipt from a cart
    Receipt(const vector<CartItem> &cart, double payment);

    // Adds a CartItem to the receipt.
    void addItem(const CartItem &item);
    

    double getTotalCostWithoutTax() const;

    // Calculates the total cost of all items in the receipt by summing the total value of each item, including tax.
    double getTotalCost() const;

    // Calculates the total tax amount of all items in the receipt by summing the tax amount of each item.
    double getTotalTax() const;

    // Calculates the change to be returned to the client based on the total cost of the items purchased.
    double getChange() const;

    // Returns a string representation of the receipt, including its ID, client ID, payment amount, date, items and total cost and change.
    string toDisplay() const;

    // Parses a comma-separated string to initialize Receipt attributes and CartItems.
    void fromString(string line);

private:
    // Returns a string with the current date and time in the format "YYYY-MM-DD HH:MM".
    string getCurrentDateTime();
};