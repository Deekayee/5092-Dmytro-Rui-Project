#include "../include/receipt.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>

const double Receipt::TAX_RATE = 0.23;
// Static member initialization
int Receipt::nextReceiptId = 1;

// Default constructor
Receipt::Receipt() : receiptId(0), clientId(0), paymentAmount(0.0), date("0000-00-00 00:00") {}

// Constructor with cart and payment
Receipt::Receipt(const vector<CartItem> &cart, double payment, int clntId)
{
    receiptId = nextReceiptId++;
    clientId = clntId;
    paymentAmount = payment;
    date = getCurrentDateTime();
    items = cart;
}

// Getters
int Receipt::getReceiptId() const
{
    return receiptId;
}

int Receipt::getClientId() const
{
    return clientId;
}

double Receipt::getPaymentAmount() const
{
    return paymentAmount;
}

const string &Receipt::getDate() const
{
    return date;
}

const vector<CartItem> &Receipt::getItems() const
{
    return items;
}

// Business logic methods
void Receipt::addItem(const CartItem &item)
{
    items.push_back(item);
}

double Receipt::getTotalCostWithoutTax() const
{
    double total = 0.0;
    for (const auto &item : items)
    {
        total += item.getTotalSaleWithoutTax();
    }
    return roundToTwoDecimals(total);
}

double Receipt::getTotalCost() const
{
    double total = 0.0;
    for (const auto &item : items)
    {
        total += item.getTotalItemSellValue();
    }
    return roundToTwoDecimals(total);
}

double Receipt::getTotalTax() const
{
    return roundToTwoDecimals(getTotalCost() - getTotalCostWithoutTax());
}

double Receipt::getChange() const
{
    return roundToTwoDecimals(paymentAmount - getTotalCost());
}

// Display method
string Receipt::toDisplay() const
{
    stringstream ss;
    int receiptOrder = 1;
    // Totals with left alignment and consistent spacing
    const int labelWidth = 20; // Width for the label column

    // Helper lambda to pad lines to full width
    auto padLine = [](const string &line, int width) -> string
    {
        if (line.length() >= width)
            return line;
        return line + string(width - line.length(), ' ');
    };

    // Header with store branding
    ss << padLine("", DISPLAY_WIDTH) << '\n';
    ss << padLine("╔" + string(DISPLAY_WIDTH - 2, '=') + "╗", DISPLAY_WIDTH) << '\n';
    ss << padLine("║" + string((DISPLAY_WIDTH - 22) / 2, ' ') + "*** RECEIPT ***" + string((DISPLAY_WIDTH - 10) / 2, ' ') + "║", DISPLAY_WIDTH) << '\n';
    ss << padLine("╚" + string(DISPLAY_WIDTH - 2, '=') + "╝", DISPLAY_WIDTH) << '\n';
    ss << padLine("", DISPLAY_WIDTH) << '\n';

    // Start with white background and black text
    ss << WHITE << BLACK; // White background + black text

    ss << padLine(string(DISPLAY_WIDTH, '='), DISPLAY_WIDTH) << '\n';

    // Header info with consistent alignment
    stringstream receiptIdSS;
    receiptIdSS << " " << setw(labelWidth) << left << "Receipt ID:" << receiptId;
    ss << padLine(receiptIdSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream clientIdSS;
    clientIdSS << " " << setw(labelWidth) << left << "Client ID:" << clientId;
    ss << padLine(clientIdSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream dateSS;
    dateSS << " " << setw(labelWidth) << left << "Date:" << date;
    ss << padLine(dateSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream itemsSS;
    itemsSS << " " << setw(labelWidth) << left << "Items:";
    ss << padLine(itemsSS.str(), DISPLAY_WIDTH) << '\n';

    ss << padLine(string(DISPLAY_WIDTH, '-'), DISPLAY_WIDTH) << '\n';

    // Table header
    stringstream headerSS;
    headerSS << setw(2) << " No" << " | "
             << setw(22) << left << "Product Name" << " | "
             << setw(5) << right << "Qtty" << " | "
             << setw(12) << right << "Price" << " | "
             << setw(12) << right << "Total";
    ss << padLine(headerSS.str(), DISPLAY_WIDTH) << '\n';

    ss << padLine(string(DISPLAY_WIDTH, '-'), DISPLAY_WIDTH) << '\n';

    // Items
    for (const auto &item : items)
    {
        ss << padLine(" " + item.toDisplay(receiptOrder++), DISPLAY_WIDTH) << '\n';
    }

    ss << padLine(string(DISPLAY_WIDTH, '-'), DISPLAY_WIDTH) << '\n';

    stringstream totalSS;
    totalSS << " " << setw(labelWidth) << left << "Total w/o Tax:"
            << fixed << setprecision(2)
            << getTotalCostWithoutTax() << " eur";
    ss << padLine(totalSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream taxSS;
    taxSS << " " << setw(labelWidth) << left << "Total Tax (23%):"
          << fixed << setprecision(2)
          << getTotalTax() << " eur";
    ss << padLine(taxSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream costSS;
    costSS << " " << setw(labelWidth) << left << "Total Cost:"
           << fixed << setprecision(2)
           << getTotalCost() << " eur";
    ss << padLine(costSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream paymentSS;
    paymentSS << " " << setw(labelWidth) << left << "Payment Amount:"
              << fixed << setprecision(2)
              << paymentAmount << " eur";
    ss << padLine(paymentSS.str(), DISPLAY_WIDTH) << '\n';

    stringstream changeSS;
    changeSS << " " << setw(labelWidth) << left << "Change:"
             << fixed << setprecision(2)
             << getChange() << " eur";
    ss << padLine(changeSS.str(), DISPLAY_WIDTH) << '\n';

    ss << padLine(string(DISPLAY_WIDTH, '-'), DISPLAY_WIDTH) << '\n';

    // Footer with thank you message
    ss << padLine("", DISPLAY_WIDTH) << '\n';
    ss << padLine(string((DISPLAY_WIDTH - 20) / 2, ' ') + "Thank you for buying", DISPLAY_WIDTH) << '\n';
    ss << padLine(string((DISPLAY_WIDTH - 20) / 2, ' ') + "in our amazing shop!", DISPLAY_WIDTH) << '\n';
    ss << padLine("", DISPLAY_WIDTH) << '\n';
    ss << padLine(string((DISPLAY_WIDTH - 23) / 2, ' ') + "Till next time friendo!", DISPLAY_WIDTH) << '\n';
    ss << padLine("", DISPLAY_WIDTH) << '\n';

    // Perforated edge effect
    ss << padLine(string(DISPLAY_WIDTH, '='), DISPLAY_WIDTH) << '\n';

    // Reset colors at the end
    ss << RESET;

    // Empty line at the end
    ss << '\n';

    return ss.str();
}

string Receipt::toString() const
{
    stringstream ss;
    ss << receiptId << "," << clientId << "," << fixed << setprecision(2) << paymentAmount << "," << date;

    // Add items separated by semicolons
    for (const auto &item : items)
    {
        ss << ";" << item.toString();
    }

    return ss.str();
}

// Parser
void Receipt::fromString(const string &line)
{
    stringstream ss(line);
    string field;

    getline(ss, field, ',');
    receiptId = stoi(field);
    getline(ss, field, ',');
    clientId = stoi(field);
    getline(ss, field, ',');
    paymentAmount = stod(field);
    getline(ss, date, ';');

    while (getline(ss, field, ';'))
    {
        CartItem item;
        item.fromString(field);
        items.push_back(item);
    }
}

// Static methods
int Receipt::getNextReceiptId()
{
    return nextReceiptId;
}

void Receipt::setNextReceiptId(int id)
{
    if (id > 0)
    {
        nextReceiptId = id;
    }
}

// helper methods
string Receipt::getCurrentDateTime() const
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-"
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min;

    return ss.str();
}

double Receipt::roundToTwoDecimals(double value) const
{
    return round(value * 100.0) / 100.0;
}
