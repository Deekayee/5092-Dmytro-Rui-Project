#pragma once
#include <string>
#include <array>
#include <vector>
#include "receipt.h"
#include "stock.h"

class SalesReport 
{
private:
    array<Receipt, 100> receipts;
    vector<Stock> stockList;
    int receiptCount;
    int maxStockId;
    
public:
    SalesReport() : receiptCount(0), maxStockId(0) {}
    
    // Initialize with data from Store
    void initialize(const array<Receipt, 100>& saleList, const vector<Stock>& stock);
    
    // Find client who bought the most in value
    int getTopClientByValue() const;
    
    // Get the most sold product by quantity
    int getMostSoldProductByQuantity() const;
    
    // Get the least sold product by quantity
    int getLeastSoldProductByQuantity() const;
    
    // Get total sales value of most sold product
    double getMostSoldProductTotalSales() const;
    
    // Calculate total stock value (sum of all products * their costValue)
    double getTotalStockValue() const;
    
    // Generate stock report with total stock
    void generateStockReport() const;
    
    // Sales report by product (receives product name as parameter)
    void generateSalesReportByProduct(const string& productName) const;
    
    // Helper methods
    double getClientTotalPurchases(int clientId) const;
    int getProductTotalQuantitySold(int stockId) const;
    double getProductTotalSales(int stockId) const;
    int countValidReceipts() const;
};
