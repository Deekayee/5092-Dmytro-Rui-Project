#include "../include/Sale.h"

int Receipt::getReceiptId() const { return receiptId; }
int Receipt::getClientId() const { return clientId; }
double Receipt::getPaymentAmount() const { return paymentAmount; }
string Receipt::getDate() const { return date; }
vector<CartItem> Receipt::getItems() const { return items; }

// Initializes a Receipt object with a unique receipt ID, client ID, current date, and default payment amount.
Receipt::Receipt() : paymentAmount(0.0)
{
    receiptId = nextReceiptId++;
    clientId = nextClientId++;
    date = getCurrentDateTime();
}

// new constructor to auto-create Receipt from a cart
Receipt::Receipt(const vector<CartItem> &cart, double payment)
{
    receiptId = nextReceiptId++;
    clientId = nextClientId++;
    paymentAmount = payment;
    date = getCurrentDateTime();
    items = cart; // simple copy of all cart items
}

// Adds a CartItem to the receipt.
void Receipt::addItem(const CartItem &item)
{
    items.push_back(item);
}

double Receipt::getTotalCostWithoutTax() const
{
    double total = 0;
    for (const auto &item : items)
    {
        total += item.getTotalSaleWithoutTax();
    }
    total = round(total * 100) / 100;
    return total;
}

// Calculates the total cost of all items in the receipt by summing the total value of each item, including tax.
double Receipt::getTotalCost() const
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
double Receipt::getTotalTax() const
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
double Receipt::getChange() const
{
    double change = round((paymentAmount - getTotalCost()) * 100) / 100;
    return change;
}

// Returns a string representation of the receipt, including its ID, client ID, payment amount, date, items and total cost and change.
string Receipt::toDisplay() const
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
void Receipt::fromString(string line)
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

// Returns a string with the current date and time in the format "YYYY-MM-DD HH:MM".
string Receipt::getCurrentDateTime()
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
