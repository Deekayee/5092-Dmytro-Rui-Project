## Dumping large comments here, to clean up code

### shop.cpp

void test()
{
    // Stock testStock(12,"TESTE",1,2.50);
    // string testString = testStock.toString();
    // cout << testString;
    createStockFile();
    vector <Stock> *StockList;
    bool flag = openStockFile(StockList);
    addPurchaseToStock(StockList);
    cin.ignore();
    return;

}
### menu.cpp
### utils.cpp
    | --------------- | ---------------------------------------------- |
    | Black           | `\033[0;30m`                                   |
    | Red             | `\033[0;31m`                                   |
    | Green           | `\033[0;32m`                                   |
    | Yellow          | `\033[0;33m`                                   |
    | Blue            | `\033[0;34m`                                   |
    | Magenta         | `\033[0;35m`                                   |
    | Cyan            | `\033[0;36m`                                   |
    | White (default) | `\033[0;37m`                                   |
    | Bright variant  | Add `1;` (e.g., `\033[1;32m` for bright green) |
    // \033[0m = reset color
### shopClasses.cpp

How this works:

Stock myCamera;
myCamera.stockId = 1;
myCamera.productName = "Sony A6000";
myCamera.quantity = 10;
myCamera.costValue = 500.0;

CartItem cartItem(myCamera, 2); // buying 2 units with 23% tax

cout << "Item total with tax: " << cartItem.getTotalItemSellValue() << endl;

-------------------------------------------------------------------------------------
for Receipt:

vector<CartItem> cart;
// Assume cart is filled with CartItem objects

double userPayment = 1300.0;
int newReceiptId = 1;
int newClientId = 1;

Receipt receipt(cart, userPayment, newReceiptId, newClientId);

cout << "Receipt total: " << receipt.getTotalCost() << endl;
cout << "Change to give: " << receipt.getChange() << endl;

-------------------------------------------------------------------------------------
Added autoincrementation

Stock camera;
camera.productName = "Canon M50";
camera.quantity = 5;
camera.costValue = 600.0;

CartItem item(camera, 2); // 2 units of this stock

vector<CartItem> cart = { item };

Receipt receipt(cart, 1500.0); // only need to pass cart and payment

cout << "Receipt ID: " << receipt.receiptId << ", Client ID: " << receipt.clientId << endl;

-------------------------------------------------------------------------------------
vector<Stock> inventory;

// Adding some stock entries
Stock cam1;
cam1.productName = "Canon M50";
cam1.quantity = 5;
cam1.costValue = 600.0;

Stock cam2;
cam2.productName = "Sony A6000";
cam2.quantity = 3;
cam2.costValue = 500.0;

inventory.push_back(cam1);
inventory.push_back(cam2);

// Display stock
for (const auto& item : inventory) {
    cout << "ID: " << item.stockId << ", Product: " << item.productName
         << ", Qty: " << item.quantity << ", Sale Value: " << item.getSaleValue() << endl;
}

-------------------------------------------------------------------------------------
    // Takes a string line from a file and parses it into Receipt object.
    // Receipt object fields are as follows:
    //  receiptId - the ID of the receipt
    //  clientId - the ID of the client
    //  paymentAmount - the amount of money the client paid
    //  date - the date when the receipt was issued
    //  items - a vector of CartItem objects, which represent the items
    //  purchased by the client.
    void fromString(string line)