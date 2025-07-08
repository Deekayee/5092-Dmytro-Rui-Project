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

    // SubMenus - management:
    void printStock(const string &title, vector<int> *idColor = nullptr, const string colorCode = "");
    void searchStock();
    bool showSearch(vector<Stock> &matchedItems);
    void addStock();
    void editStock();
    void removeStock();
    //  SubMenus - reports:
    void generateStockReport(SalesReport &report);
    void generateSalesReportByProduct(SalesReport &report);
    void generateCompleteSalesReport(SalesReport &report);
    void showMostSoldProduct(SalesReport &report);
    void showLeastSoldProduct(SalesReport &report);
    void showTopClient(SalesReport &report);
    // SubMenus - shopping:
    void printProducts();
    void printCart();
    void addProductCart();
    void removeProductCart();
    void changeProductCart();
    void checkoutMenu();
    double processPayment(double total);                                 // (asks for payment, prints messages)
    void completeCheckout(Client *client, double payment, double total); //(prints receipt, messages, pauses)
    void gambling(vector<CartItem> &sale, int chance = 50);              //(prints win message)
    // void clearCart(vector<Stock> *shelf = nullptr); //(partially UI : prints messages and pauses)
    //  SubMenus - logins:
    void printClients(const string &title, vector<int> *idColor = nullptr, const string colorCode = "");
    Client *handleClientSelection(); 
    Client *registerClient();
    void killClient();
    void changeClientName();

public:
    Menu(Store &storeReference);

    void main();
    // Main() options:
    void management();
    void shopping();
    void reports();
    void logins();
};