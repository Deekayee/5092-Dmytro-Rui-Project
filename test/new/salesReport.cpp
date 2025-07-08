#include "salesReport.h"
#include "cartItem.h"

#include <climits>

void SalesReport::initialize(const array<Receipt, 100>& saleList, const vector<Stock>& stock)
{
    receipts = saleList;
    stockList = stock;
    receiptCount = countValidReceipts();
    maxStockId = stockList.size();
}

int SalesReport::countValidReceipts() const
{
    int count = 0;
    for (int i = 0; i < 100; i++) {
        if (receipts[i].getReceiptId() > 0) { // Assuming valid receipts have ID > 0
            count++;
        }
    }
    return count;
}

int SalesReport::getTopClientByValue() const
{
    int topClient = -1;
    double maxAmount = 0;
    
    // Check each receipt to find unique clients
    for (int i = 0; i < receiptCount; i++) {
        if (receipts[i].getReceiptId() > 0 && receipts[i].getClientId() > 0) {
            int currentClient = receipts[i].getClientId();
            double clientTotal = getClientTotalPurchases(currentClient);
            
            if (clientTotal > maxAmount) {
                maxAmount = clientTotal;
                topClient = currentClient;
            }
        }
    }
    
    return topClient;
}

int SalesReport::getMostSoldProductByQuantity() const
{
    int mostSoldProduct = -1;
    int maxQuantity = 0;
    
    // Check each product ID from 1 to maxStockId
    for (int productId = 1; productId <= maxStockId; productId++) {
        int totalQuantity = getProductTotalQuantitySold(productId);
        
        if (totalQuantity > maxQuantity) {
            maxQuantity = totalQuantity;
            mostSoldProduct = productId;
        }
    }
    
    return mostSoldProduct;
}

int SalesReport::getLeastSoldProductByQuantity() const
{
    int leastSoldProduct = -1;
    int minQuantity = INT_MAX;

    for (int productId = 1; productId <= maxStockId; productId++) {
        int totalQuantity = getProductTotalQuantitySold(productId);
        
        // Skip products that were never sold
        if (totalQuantity == 0) {
            continue;
        }

        if (totalQuantity < minQuantity) {
            minQuantity = totalQuantity;
            leastSoldProduct = productId;
        }
    }

    return leastSoldProduct;
}

double SalesReport::getMostSoldProductTotalSales() const
{
    int mostSoldProductId = getMostSoldProductByQuantity();
    return getProductTotalSales(mostSoldProductId);
}

double SalesReport::getTotalStockValue() const
{
    double totalValue = 0;
    
    for (const auto& stock : stockList) {
        totalValue += stock.getQuantity() * stock.getCostValue();
    }
    
    return totalValue;
}

void SalesReport::generateStockReport() const
{    
    double totalStockValue = 0;
    
    for (const auto& stock : stockList) {
        double productTotal = stock.getQuantity() * stock.getCostValue();
        totalStockValue += productTotal;
    }
    cout << "Total stock value: " << fixed << setprecision(2) << totalStockValue  << " eur." << endl;
}

void SalesReport::generateSalesReportByProduct(const string& productName) const
{
    cout << "Report for product: " << productName << endl;
    
    //HACK: this is AI shenenigans, needs to be redone as we have a method for this in store
    // Find product ID by name
    int productId = -1;
    for (const auto& stock : stockList) {
        if (stock.getProductName() == productName) {
            productId = stock.getStockId();
            break;
        }
    }
    
    if (productId == -1) {
        cout << "Product not found!" << endl;
        return;
    }
    
    int totalQuantitySold = getProductTotalQuantitySold(productId);
    double totalSalesValue = getProductTotalSales(productId);
    
    cout << "Product ID: " << productId << endl;
    cout << "Product Name: " << productName << endl;
    cout << "Total Quantity Sold: " << totalQuantitySold << endl;
    cout << "Total Sales Value: " << fixed << setprecision(2) << totalSalesValue << " eur." << endl;
    
    // Show individual sales
    cout << "\nIndividual Sales:" << endl;
    cout << "Receipt ID | Quantity | Sale Value" << endl;
    cout << "----------------------------------" << endl;
    
    for (int i = 0; i < receiptCount; i++) {
        if (receipts[i].getReceiptId() > 0) {
            for (const auto& item : receipts[i].getItems()) {
                if (item.getStockId() == productId) {
                    cout << receipts[i].getReceiptId() << " | " 
                         << item.getQuantity() << " | " 
                         << fixed << setprecision(2) << item.getTotalItemSellValue() << endl;
                }
            }
        }
    }
}

// Helper methods
double SalesReport::getClientTotalPurchases(int clientId) const
{
    double total = 0;
    for (int i = 0; i < receiptCount; i++) {
        if (receipts[i].getReceiptId() > 0 && receipts[i].getClientId() == clientId) {
            total += receipts[i].getTotalCost();
        }
    }
    return total;
}

int SalesReport::getProductTotalQuantitySold(int stockId) const
{
    int total = 0;
    for (int i = 0; i < receiptCount; i++) {
        if (receipts[i].getReceiptId() > 0) {
            for (const auto& item : receipts[i].getItems()) {
                if (item.getStockId() == stockId) {
                    total += item.getQuantity();
                }
            }
        }
    }
    return total;
}

double SalesReport::getProductTotalSales(int stockId) const
{
    double total = 0;
    for (int i = 0; i < receiptCount; i++) {
        if (receipts[i].getReceiptId() > 0) {
            for (const auto& item : receipts[i].getItems()) {
                if (item.getStockId() == stockId) {
                    total += item.getTotalSaleWithoutTax();
                }
            }
        }
    }
    return total;
}