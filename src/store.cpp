#include "../include/store.h"

Store::Store()
{
    // Initialize DataBase
    // - open stock, client and sale files
    // - fill stock and client vectors
    // - fill out sale *special* vector (limit 100)
    // - loadup start menu
    initializeData();
}

bool Store::initializeData()
{
    int errorCheck = 0;
    errorCheck += FileManager::loadStockFromFile("stockList.csv", stockList);
    errorCheck += FileManager::loadClientsFromFile("clientList.csv", clientList);
    errorCheck += FileManager::loadReceiptsFromFile("saleList.csv", saleList);

    if (errorCheck != 3)
        return false;
}