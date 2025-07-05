#pragma once

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
    void addStock();
    void editStock();
    void removeStock();

public:
    Menu(Store &storeReference);

    void main();
};