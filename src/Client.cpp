#include "../include/Client.h"


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
    CartItem() : stockId(0), quantity(0), saleWithoutTax(0.0), taxRatePercent(0.0), productName("") {}

    // Construct a CartItem from a Stock item, quantity and tax rate (default = 23%)
    CartItem(const Stock &stock, int qty, double taxRate = 23.0)
    {
        stockId = stock.getStockId();
        productName = stock.getProductName();
        quantity = qty;
        taxRatePercent = taxRate;
        saleWithoutTax = stock.getSaleValue();
    }

    int getStockId() const { return stockId; }
    int getQuantity() const { return quantity; }
    double getSaleWithoutTax() const { return saleWithoutTax; }
    double getTaxRatePercent() const { return taxRatePercent; }
    string getProductName() const { return productName; }

    void setStockId(int id) { stockId = id; }
    void setQuantity(int qty) { quantity = qty; }
    void setSaleWithoutTax(double price) { saleWithoutTax = price; }
    void setTaxRatePercent(double rate) { taxRatePercent = rate; }
    void setProductName(string name) { productName = name; }

    // Calculates and returns the sale value of the item including tax by applying the tax rate to the sale value without tax.
    double getSaleWithTax() const
    {
        return saleWithoutTax * (1 + taxRatePercent / 100.0);
    }

    // Returns the total value of the item in the cart, without tax.
    double getTotalSaleWithoutTax() const
    {
        return saleWithoutTax * quantity;
    }

    // Returns the total value of the item in the cart, including tax.
    double getTotalItemSellValue() const
    {
        return getSaleWithTax() * quantity;
    }

    // Returns a string with the CartItem attributes in CSV format.
    string toString() const
    {
        stringstream ss;
        ss << stockId << ',' << productName << ',' << quantity << ',' << fixed << setprecision(2) << saleWithoutTax << ',' << fixed << setprecision(2) << taxRatePercent << ',' << fixed << setprecision(2) << getSaleWithTax() << ',' << fixed << setprecision(2) << getTotalItemSellValue();
        return ss.str();
    }

    string toDisplay() const
    {
        stringstream ss;
        ss << setw(2) << stockId << " | "
           << setw(22) << left << productName << " | "
           << setw(5) << right << quantity << " | "
           << setw(8) << right << fixed << setprecision(2) << getSaleWithTax() << " eur | "
           << setw(9) << right << fixed << setprecision(2) << getTotalItemSellValue() << " eur";

        return ss.str();
    }

    // Parses a comma-separated string to initialize CartItem attributes.
    void fromString(string line)
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
        getline(ss, field, ',');
        taxRatePercent = stod(field);
        getline(ss, field, ',');
        double saleWithTax = stod(field);
        getline(ss, field);
        double totalItemSellValue = stod(field);
    }
};
