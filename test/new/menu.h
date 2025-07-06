#pragma once

#include "stock.h"
#include <vector>


using namespace std;

class Store;
class Menu
{
private:
    Store &store;
    bool menuState = 0;

    // Main() options:
    void management();
    void shopping();
    void logins();
    // SubMenus - management:
    void searchStock();
    bool showSearchResults(vector <Stock>& matchedItems);
    void addStock();
    void editStock();
    void removeStock();

public:
    Menu(Store &storeReference);

    void main();
};