#pragma once

#include "stock.h"
#include "cartItem.h"
#include "client.h"
#include "receipt.h"
#include "salesReport.h"
#include "utils.h"

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
    void printStock(const string &title, vector<int> *idColor = nullptr, const string colorCode = "");
    void searchStock();
    bool showSearch(vector<Stock> &matchedItems);
    void addStock();
    void editStock();
    void removeStock();
    // SubMenus - shopping:
    void printProducts();
    void printCart();
    void addProductCart(bool menuState);
    void removeProductCart(bool menuState);
    void changeProductCart(bool menuState);
    void checkoutMenu();
    double processPayment(double total);                                 // (asks for payment, prints messages)
    void completeCheckout(Client *client, double payment, double total); //(prints receipt, messages, pauses)
    void gambling(vector<CartItem> &sale, int chance = 50);              //(prints win message)
    // void clearCart(vector<Stock> *shelf = nullptr); //(partially UI : prints messages and pauses)
    //  SubMenus - logins:
    void printClients();
    Client *handleClientSelection(); // (asks for user input, prints messages)
    Client *createNewClient();       //(should prompt for user input and print messages; currently missing implementation)

public:
    Menu(Store &storeReference);

    void main();
};