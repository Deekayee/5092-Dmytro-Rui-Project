#include "fileManager.h"

#include "receipt.h"

#include <iostream>
#include <fstream>
#include <array>

bool FileManager::loadStock(vector<Stock> &stockList)
{
    fstream file("stockList.csv", ios::in);
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return false;
    }

    string line;
    getline(file, line); // ignore header
    int maxId = 0;
    while (getline(file, line))
    {
        Stock item;
        item.fromString(line);
        stockList.push_back(item);

        // Track the highest ID
        if (item.getStockId() > maxId)
            maxId = item.getStockId();
    }

    // Set the nextStockId to one greater than the highest existing ID
    Stock::setNextStockId(maxId + 1);

    file.close();
    return true;
}

bool FileManager::saveStock(const vector<Stock> &stockList)
{
    ofstream file("stockList.csv");
    if (!file.is_open())
    {
        cout << "Error opening file: " << "stockList.csv" << endl;
        return false;
    }

    file << "StockId,ProductName,Quantity,CostValue" << endl;
    for (const Stock &item : stockList)
    {
        file << item.toString() << endl;
    }

    file.close();
    return true;
}

bool FileManager::loadClients(vector<Client> &clientList)
{
    fstream file("clientList.csv", ios::in);
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return false;
    }

    string line;
    getline(file, line);
    int maxId = 0;

    while (getline(file, line))
    {
        Client client;
        client.fromString(line);
        clientList.push_back(client);

        // Track the highest ID
        if (client.getClientId() > maxId)
            maxId = client.getClientId();
    }

    // Set the nextStockId to one greater than the highest existing ID
    Client::setNextId(maxId + 1);

    file.close();
    return true;
}

bool FileManager::saveClients(const vector<Client> &clientList)
{
    ofstream file("clientList.csv");
    if (!file.is_open())
    {
        cout << "Error opening file: " << "clientList.csv" << endl;
        return false;
    }

    file << "ClientId,Name,Contact,Address" << endl;
    for (const Client &client : clientList)
    {
        file << client.toString() << endl;
    }

    file.close();
    return true;
}

bool FileManager::loadReceipts(array<Receipt, 100> &saleList)
{
    fstream file("receiptList.csv", ios::in);
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return false;
    }

    string line;
    getline(file, line); // ignore header
    int maxId = 0;
    int i = 0; // Initialize i to 0
    
    while (getline(file, line) && i < 100) // Add bounds check
    {
        if (!line.empty()) // Check if line is not empty
        {
            Receipt sale;
            sale.fromString(line);
            saleList.at(i) = sale;

            // Track the highest ID
            if (sale.getReceiptId() > maxId)
                maxId = sale.getReceiptId();
            
            i++; // Increment i
        }
    }

    // Set the nextReceiptId to one greater than the highest existing ID
    Receipt::setNextReceiptId(maxId + 1);

    file.close();
    return true;
}

bool FileManager::saveReceipts(const array<Receipt, 100> &saleList)
{
    ofstream file("receiptList.csv");
    if (!file.is_open())
    {
        cout << "Error opening file: " << "receiptList.csv" << endl;
        return false;
    }

    file << "ReceiptId,ClientId,PaymentAmount,Date,Items" << endl;
    
    for (int i = 0; i < 100; i++)
    {
        if (saleList.at(i).getReceiptId() > 0) // Only save valid receipts
        {
            file << saleList.at(i).toString() << endl;
        }
    }

    file.close();
    return true;
}