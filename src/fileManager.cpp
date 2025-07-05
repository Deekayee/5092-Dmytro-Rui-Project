#include "../include/fileManager.h"

#include <iostream>
#include <fstream>

bool FileManager::loadStockFromFile(const string &filename, vector<Stock> &stockList)
{
    fstream file(filename, ios::in);
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

bool FileManager::saveStockToFile(const string &filename, const vector<Stock> &stockList)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
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

bool FileManager::loadClientsFromFile(const string &filename, vector<Client> &clientList)
{
    fstream file(filename, ios::in);
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

bool FileManager::saveClientsToFile(const string &filename, const vector<Client> &clientList)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
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

bool FileManager::loadReceiptsFromFile(const string &filename, array<Receipt, 100> &saleList)
{
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return false;
    }

    string line;
    getline(file, line); // ignore header
    int maxId = 0;
    int i;
    while (getline(file, line))
    {
        Receipt sale;
        sale.fromString(line);
        saleList.at(i) = sale;

        // Track the highest ID
        if (sale.getReceiptId() > maxId)
            maxId = sale.getReceiptId();
    }

    // Set the nextStockId to one greater than the highest existing ID
    Receipt::setNextReceiptId(maxId + 1);

    file.close();
    return true;
}

bool FileManager::saveReceiptsToFile(const string &filename, const array<Receipt, 100> &saleList)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    file << "ReceiptId,ClientId,PaymentAumount,Date,Items" << endl;
    for (int i = 0; i < 100; i++)
    {
        file << saleList.at(i).toString() << endl;
    }

    file.close();
    return true;
}