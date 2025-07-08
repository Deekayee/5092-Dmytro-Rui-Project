#include "salesReport.h"
#include "cartItem.h"

#include <climits>

// Initialize with data from Store
void SalesReport::initialize(const array<Receipt, 100> &saleList, const vector<Stock> &stock)
{
    receipts = saleList;
    stockList = stock;
    receiptCount = countValidReceipts();
    maxStockId = stockList.size();
}

// Helper methods
int SalesReport::countValidReceipts() const
{
    int count = 0;
    for (int i = 0; i < 100; i++)
    {
        if (receipts[i].getReceiptId() > 0)
        { // Assuming valid receipts have ID > 0
            count++;
        }
    }
    return count;
}

// Find client who bought the most in value
int SalesReport::getTopClientByValue() const
{
    int topClient = -1;
    double maxAmount = 0;

    // Check each receipt to find unique clients
    for (int i = 0; i < receiptCount; i++)
    {
        if (receipts[i].getReceiptId() > 0 && receipts[i].getClientId() > 0)
        {
            int currentClient = receipts[i].getClientId();
            double clientTotal = getClientTotalPurchases(currentClient);

            if (clientTotal > maxAmount)
            {
                maxAmount = clientTotal;
                topClient = currentClient;
            }
        }
    }

    return topClient;
}

// Find product that was sold the most
int SalesReport::getMostSoldProductByQuantity() const
{
    int mostSoldProduct = -1;
    int maxQuantity = 0;

    // Check each product ID from 1 to maxStockId
    for (int productId = 1; productId <= maxStockId; productId++)
    {
        int totalQuantity = getProductTotalQuantitySold(productId);

        if (totalQuantity > maxQuantity)
        {
            maxQuantity = totalQuantity;
            mostSoldProduct = productId;
        }
    }

    return mostSoldProduct;
}

// Find product that was sold the least
int SalesReport::getLeastSoldProductByQuantity() const
{
    int leastSoldProduct = -1;
    int minQuantity = INT_MAX;

    for (int productId = 1; productId <= maxStockId; productId++)
    {
        int totalQuantity = getProductTotalQuantitySold(productId);

        // Skip products that were never sold
        if (totalQuantity == 0)
        {
            continue;
        }

        if (totalQuantity < minQuantity)
        {
            minQuantity = totalQuantity;
            leastSoldProduct = productId;
        }
    }

    return leastSoldProduct;
}

// Get total sales value of most sold product
double SalesReport::getMostSoldProductTotalSales() const
{
    int mostSoldProductId = getMostSoldProductByQuantity();
    return getProductTotalSales(mostSoldProductId);
}

// Calculate total stock value
double SalesReport::getTotalStockValue() const
{
    double totalValue = 0;

    for (const auto &stock : stockList)
    {
        totalValue += stock.getQuantity() * stock.getCostValue();
    }

    return totalValue;
}

// Generate stock report
void SalesReport::generateStockReport() const
{
    double totalStockValue = 0;

    for (const auto &stock : stockList)
    {
        double productTotal = stock.getQuantity() * stock.getCostValue();
        totalStockValue += productTotal;
    }
    cout << "Total stock value: " << fixed << setprecision(2) << totalStockValue << " eur." << endl;
    limh(REPORTS_DASH);
}

// Generate sales report
void SalesReport::generateSalesReportByProduct(const string &productName) const
{
    clearConsole();
    string title = "Sales Report for: " + productName;
    int titleDASH = REPORTS_DASH - title.length();

    setColor(YELLOW);
    cout << title;
    setColor(RESET);
    limh(titleDASH);

    // Find product ID by name
    int productId = -1;
    for (const auto &stock : stockList)
    {
        if (stringToLower(stock.getProductName()) == stringToLower(productName))
        {
            productId = stock.getStockId();
            break;
        }
    }

    if (productId == -1)
    {
        setColor(RED);
        cout << "Product not found!" << endl;
        setColor(RESET);
        limh();
        return;
    }

    int totalQuantitySold = getProductTotalQuantitySold(productId);
    double totalSalesValue = getProductTotalSales(productId);

    // Product summary section
    setColor(CYAN);
    cout << "Product Summary:" << endl;
    setColor(RESET);
    cout << "Product ID: " << productId << endl;
    cout << "Product Name: " << productName << endl;
    cout << "Total Quantity Sold: " << totalQuantitySold << endl;
    cout << "Total Sales Value: " << fixed << setprecision(2) << totalSalesValue << " eur." << endl;

    limh(REPORTS_DASH);

    // Individual sales section
    setColor(CYAN);
    cout << "Individual Sales:" << endl;
    setColor(RESET);

    setColor(CYAN);
    cout << "Receipt ID | Quantity | Sale Value" << endl;
    setColor(RESET);
    limh(REPORTS_DASH);

    bool foundSales = false;
    for (int i = 0; i < receiptCount; i++)
    {
        if (receipts[i].getReceiptId() > 0)
        {
            for (const auto &item : receipts[i].getItems())
            {
                if (item.getStockId() == productId)
                {
                    foundSales = true;
                    stringstream ss;
                    ss << setw(10) << right << receipts[i].getReceiptId() << " | "
                       << setw(8) << right << item.getQuantity() << " | "
                       << setw(8) << right << fixed << setprecision(2) << item.getTotalItemSellValue() << " eur.";
                    cout << ss.str() << endl;
                }
            }
        }
    }

    if (!foundSales)
    {
        setColor(RED);
        cout << "No sales found for this product." << endl;
        setColor(RESET);
    }

    limh(REPORTS_DASH);
}

// Get total sales value of client
double SalesReport::getClientTotalPurchases(int clientId) const
{
    double total = 0;
    for (int i = 0; i < receiptCount; i++)
    {
        if (receipts[i].getReceiptId() > 0 && receipts[i].getClientId() == clientId)
        {
            total += receipts[i].getTotalCost();
        }
    }
    return total;
}

// Get total quantity sold of product
int SalesReport::getProductTotalQuantitySold(int stockId) const
{
    int total = 0;
    for (int i = 0; i < receiptCount; i++)
    {
        if (receipts[i].getReceiptId() > 0)
        {
            for (const auto &item : receipts[i].getItems())
            {
                if (item.getStockId() == stockId)
                {
                    total += item.getQuantity();
                }
            }
        }
    }
    return total;
}

// Get total sales value of product without tax
double SalesReport::getProductTotalSales(int stockId) const
{
    double total = 0;
    for (int i = 0; i < receiptCount; i++)
    {
        if (receipts[i].getReceiptId() > 0)
        {
            for (const auto &item : receipts[i].getItems())
            {
                if (item.getStockId() == stockId)
                {
                    total += item.getTotalSaleWithoutTax();
                }
            }
        }
    }
    return total;
}