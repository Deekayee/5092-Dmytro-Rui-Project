#include "store.h"

// private
bool Store::dataInit()
{
    int errorCheck = 0;
    errorCheck += FileManager::loadStock(this->stockList);
    errorCheck += FileManager::loadClients(this->clientList);
    errorCheck += FileManager::loadReceipts(this->receiptList);

    if (errorCheck != 5)
        return false;
    return true;
}

bool Store::dataUpdate()
{
    int errorCheck = 0;
    errorCheck += FileManager::saveStock(this->stockList);
    errorCheck += FileManager::saveClients(this->clientList);
    errorCheck += FileManager::saveReceipts(this->receiptList);

    if (errorCheck != 5)
        return false;
    return true;
}

void Store::updateStockFromShelf()
{
    for (Stock &shelf_item : shelf)
    {
        int id = shelf_item.getStockId();
        Stock *stock_item = Store::findStockById(id);
        Store::changePurchaseStock(stock_item, shelf_item);
    }
    cout << "Stock Updated!" << endl;
}

// public
Store::Store() : menu(*this)
{
    if (Store::dataInit() == false)
    {
        string buffer;
        cout << "Error: Failed to load data base. Please check with the developers!" << endl;
        cout << "Please enter Ctrl + C to kill task.";
        getline(cin, buffer);
    }
}

// Stock Management
vector<Stock> &Store::getStock()
{
    return stockList;
}

Stock *Store::findStockById(int stockId)
{
    for (Stock &stock : stockList)
    {
        if (stock.getStockId() == stockId)
            return &stock;
    }
    return nullptr;
}

Stock *Store::findStockByName(const string &name)
{
    string lowerName = stringToLower(name);
    for (Stock &stock : stockList)
    {
        if (stringToLower(stock.getProductName()) == lowerName)
            return &stock;
    }
    return nullptr;
}

vector<Stock> Store::searchPurchaseStock(const string &name)
{
    vector<Stock> items;
    string lowerName = stringToLower(name);
    for (Stock i : stockList)
    {
        string lowerProduct = stringToLower(i.getProductName());
        if (lowerProduct.find(lowerName) != string::npos)
        {
            items.push_back(i);
        }
    }
    return items;
}

void Store::removePurchaseStock(Stock *item)
{
    item->setQuantity(0);
    FileManager::saveStock(stockList);
}

void Store::addPurchaseStock(Stock *item)
{
    stockList.push_back(*item);
    if (FileManager::saveStock(stockList))
        cout << "Stock Updated!" << endl;
    cout << endl
         << "Item ID: " << item->getStockId() << " added in stockpile!" << endl;
}

void Store::changeQuantityStock(Stock *item, int quantity)
{
    item->setQuantity(quantity);
    FileManager::saveStock(stockList);
}

void Store::changePurchaseStock(Stock *olditem, Stock newitem)
{
    olditem->setProductName(newitem.getProductName());
    olditem->setQuantity(newitem.getQuantity());
    olditem->setCostValue(newitem.getCostValue());

    FileManager::saveStock(stockList);
}

void Store::printStock(const string &title, vector<int> *idColor, const string colorCode)
{
    clearConsole();
    int titleDASH = STOCK_DASH - title.length(); // to make sure it fits the rest of the horizontal lims

    setColor(YELLOW);
    cout << title;
    setColor(RESET);
    limh(titleDASH);

    setColor(CYAN);
    cout << "ID | Product Name           | Quantity | Cost (eur)" << endl;
    setColor(RESET);
    limh();

    for (const Stock &item : stockList)
    {
        if (item.getQuantity() == 0)
            setColor(RED); // red for zero quantity
        if (idColor != nullptr)
            for (int id : *idColor)
            {
                if (item.getStockId() == id)
                    setColor(colorCode); // <color> for when item matches vector idColor
            }

        cout << item.toDisplay() << endl;

        setColor(RESET); // resets color
    }

    limh();
}

void Store::printProducts()
{
    // just for pretty formatting
    int titleLength = 13;

    clearConsole();
    setColor(YELLOW);
    cout << "Products View";
    setColor(RESET);
    limh(PRODUCTS_DASH - titleLength);

    setColor(CYAN);
    cout << "ID | Product Name           | Quantity | Price w/Tax (eur)" << endl;
    setColor(RESET);
    limh(PRODUCTS_DASH);

    for (const Stock &item : shelf)
    {
        if (item.getQuantity() == 0)
            setColor(RED); // red for zero quantity

        stringstream ss;
        cout << setw(2) << right << item.getStockId() << " | "
             << setw(22) << left << item.getProductName() << " | "
             << setw(8) << right << item.getQuantity() << " | "
             << fixed << setprecision(2) << item.getSaleValue() * 1.23 << " eur"
             << endl;

        setColor(RESET); // resets color
    }

    limh(PRODUCTS_DASH);
}

// Cart Management

CartItem *Store::findItemCart(int id, int *index)
{
    for (int i = 0; i < cart.size(); i++)
    {
        if (cart.at(i).getStockId() == id)
        {
            if (index != nullptr)
                *index = i;
            return &cart.at(i); // finds and returns reference to item
        }
    }
    return nullptr;
}
void Store::addProductCart(bool menuState)
{
    while (true)
    {

        // prints visible menu

        clearConsole();
        if (menuState == false)
            Store::printProducts();
        else
            Store::printCart();

        int id = getValidatedInt("Insert product ID to add to cart (Enter 0 to return): ", true);
        if (id == 0)
            return;

        // checks initial quantity in stock and its existence
        Stock *item = Store::findStockById(id);
        if (item == nullptr)
        {

            cout << endl
                 << "Try another ID" << endl;
            pause();
            continue;
        }
        if (item->getQuantity() == 0)
        {
            cout << endl
                 << "Out of Stock. " << endl;
            pause();
            continue;
        }

        /*verify item quantity is valid*/
        // needs cycle to ensure cartitem is created, or function is exited
        int quantity = getValidatedInt("How many do you want good sir? (Enter 0 to return): ");
        string input;

        CartItem *bagged_item = findItemCart(item->getStockId());
        if (bagged_item != nullptr) // item exists in cart
        {

            // checking if input quantity doesn't exceed quantity in shelf
            if (item->getQuantity() >= quantity)
            {
                bagged_item->setQuantity(bagged_item->getQuantity() + quantity); // add the input quantity to existing quantity
                item->setQuantity(item->getQuantity() - quantity);               // remove the input quantity from shelf
            }
            else // quantity exceeds, ask user if it should add all remaining quantity anyway
            {
                cout << "Quantity asked exceeds quantity in stock."
                     << endl;

                stringstream ss;
                ss << "Do you wish to buy all " << item->getQuantity() << " existing items instead?";
                if (promptYESOrNo(ss.str()))
                {
                    bagged_item->setQuantity(item->getQuantity()); // if confirmed will add all existing stock items to cart
                    item->setQuantity(0);                          // as we add to cart, we remove from shelf
                }
            }
        }
        else // bagged item was not found (nullptr) and needs to be created
        {
            // checks again if input quantity doesn't exceed stock quantity
            if (item->getQuantity() >= quantity)
            {
                CartItem newItemCart(*item, quantity); // create the new bagged item
                cart.push_back(newItemCart);           // add the new bagged item the vector cart
                item->setQuantity(item->getQuantity() - quantity);
            }
            else // if exceeds
            {
                cout << "Quantity asked exceeds quantity in stock."
                     << endl;

                stringstream ss;
                ss << "Do you wish to buy all " << item->getQuantity() << " existing items instead?";
                if (promptYESOrNo(ss.str()))
                {
                    CartItem newItemCart(*item, item->getQuantity()); // create the new bagged item
                    cart.push_back(newItemCart);                      // add the new bagged item the vector cart
                    item->setQuantity(0);
                }
            }
        }

        cout << "Cart Updated!" << endl;

        if (promptyesOrNO("Do you wish to continue adding?"))
            continue;
        else
            return;
    }
}
void Store::removeProductCart(bool menuState)
{
    while (true)
    {
        clearConsole();

        if (menuState == false)
            Store::printProducts();
        else
            Store::printCart();
        int id = getValidatedInt("Insert product ID to remove (Enter 0 to return): ", true);
        if (id == 0)
            return;

        int index;
        CartItem *bagged_item = findItemCart(id, &index);
        Stock *item = Store::findStockById(id);

        string input;
        if (bagged_item != nullptr)
        {
            cart.erase(cart.begin() + index);
            item->setQuantity(item->getQuantity() + bagged_item->getQuantity());

            cout << "Product removed from cart." << endl;
            if (!promptyesOrNO("Do you wish to continue removing?"))
            {
                break;
            }
        }
        else
        {
            cout << "Item not found." << endl;
            if (!promptyesOrNO("Do you wish to continue removing?"))
            {
                break;
            }
        }
    }
}
void Store::changeProductCart(bool menuState)
{
    while (true)
    {

        clearConsole();
        if (menuState == false)
            Store::printProducts();
        else
            Store::printCart();

        int id = getValidatedInt("Insert product ID in cart to change (Enter 0 to return): ", true);
        if (id == 0)
            return;

        CartItem *bagged_item = Store::findItemCart(id);
        if (bagged_item) // if item exists in cart
        {

            Stock *item = Store::findStockById(id);

            int item_quantity = item->getQuantity();
            int bagged_quantity = bagged_item->getQuantity();
            int quantity = getValidatedInt("Insert new quantity: ", false);
            quantity = quantity - bagged_item->getQuantity(); // will be the added/removed quantity from either cart or shelf

            if (quantity > item->getQuantity())
            {
                cout << "Not enough stock."
                     << endl;

                stringstream ss;
                ss << "Do you wish to buy all " << item->getQuantity() << " remaining items instead? ";
                if (promptYESOrNo(ss.str()))
                {
                    bagged_item->setQuantity(item_quantity + bagged_quantity);
                    item->setQuantity(0);
                }
                else
                    return;
            }
            else
            {
                bagged_item->setQuantity(quantity + bagged_quantity);
                item->setQuantity(item_quantity - quantity);
            }
            cout << "Product quantity changed." << endl;
            if (!promptyesOrNO("Do you want to continue adjusting? "))
                return;
        }
        else // if it doesn't exist in cart, refuse to update
        {
            string input;
            cout << "Product not found in cart. Please select a valid ID" << endl;
            if (!promptyesOrNO("Do you want to continue adjusting? "))
                return;
        }
    }
}
void Store::clearCart(vector<Stock> *shelf)
{
    if (cart.empty())
    {
        cout << "Cart is already empty";
        pause();
        return;
    }

    // *this case represents a canceled sale through the menu
    // here we need to bring back the quantities in the cart back to the shelf
    // before deleting them
    if (shelf != nullptr)
        for (CartItem &bagged_item : cart)
        {
            // update
            Stock *item = Store::findStockById(bagged_item.getStockId());
            item->setQuantity(bagged_item.getQuantity() + item->getQuantity());
        }

    // *otherwise, if shelf isnt specified, it means checkout is happening, so
    // the shelf already owns the correct quantities and is ready to update our
    // stockList
    cart.clear();
    cout << "Cart cleared." << endl;
}

void Store::printCart()
{
    int titleDASH = CART_DASH - 9; // to make sure it fits the rest of the horizontal lims
    clearConsole();
    setColor(YELLOW);
    cout << "Your cart";
    setColor(RESET);

    limh(titleDASH);
    setColor(CYAN);
    cout << setw(2) << "ID" << " | "
         << setw(22) << left << "Product Name" << " | "
         << setw(5) << right << "Qtty" << " | "
         << setw(12) << right << "Price" << " | "
         << setw(12) << right << "Total"
         << endl;
    setColor(RESET);
    limh(CART_DASH);
    if (cart.empty())
    {
        cout << "Cart is empty." << endl;
        limh(CART_DASH);
        return;
    }
    for (const CartItem &cartItem : cart)
    {
        cout << cartItem.toDisplay() << endl;
    }

    limh(CART_DASH);
}

// Client Management

Client *Store::findClientById(int clientId)
{
    for (Client &compareClient : clientList)
    {
        compareClient.getClientId()==clientId;
        return &compareClient;
    }
    return nullptr;
    
}

Client *Store::findClientByName(const string &name)
{
    string lowerName = stringToLower(name);
    for (Client &compareClient : clientList)
    {
        string clientName = compareClient.getName();
        if(stringToLower(clientName) == lowerName)
            return &compareClient;
    }
    return nullptr;
    
}

void Store::addClient(Client &newClient)
{
    clientList.push_back(newClient);
    return;
}

void Store::removeClient(Client &killClient);
{
    return
}

void Store::printClients();
{

}


// Sales Management

void Store::checkoutMenu()
{
    if (cart.empty())
    {
        cout << "Cart is empty." << endl;
        pause();
        return;
    }

    // Display cart and calculate total
    clearConsole();
    cout << "Your cart:" << endl;
    Store::printCart();

    double total = Store::calculateCartTotal();
    cout << "Total: " << total << " eur" << endl;

    if (!promptYESOrNo("Do you wish to confirm?"))
        return;

    // Handle client selection/creation
    Client *selectedClient = Store::handleClientSelection();

    // Process payment
    double payment = Store::processPayment(total);
    if (payment < 0) // User cancelled payment
        return;

    // Complete checkout
    Store::completeCheckout(selectedClient, payment, total);
}

double Store::calculateCartTotal()
{
    double total = 0;
    for (const CartItem &item : cart)
    {
        total += item.getTotalItemSellValue();
    }
    return round(total * 100) / 100;
}

Client *Store::handleClientSelection()
{
    if (promptyesOrNO("Are you part of our extremely cool clientele?"))
    {
        cout << "Enter your name: ";
        string name;
        getline(cin, name);

        Client *client = Store::findClientByName(name);
        if (client)
        {
            cout << "Welcome back, " << client->getName() << ", you son of your mother!" << endl;
            return client;
        }
        else
        {
            cout << "Client not found." << endl;
            if (promptyesOrNO("Would you like to register as a new client?"))
            {
                return createNewClient();
            }
        }
    }
    else if (promptyesOrNO("But do you want to be part of the cool kids club?"))
    {
        return createNewClient();
    }

    // Return default client (guest checkout)
    return nullptr; // We'll handle this in completeCheckout
}

Client *Store::createNewClient()
{
    // Add client creation logic here
    Store::addClient();
    // Return pointer to the newly created client
    return &clientList.back(); // Assuming addClient adds to the end
}

double Store::processPayment(double total)
{
    double payment = getValidatedDouble("Insert payment amount: ");

    while (payment < total)
    {
        cout << "Nice joke, that's not enough." << endl;
        if (promptYESOrNo("Do you want to try again?"))
            payment = getValidatedDouble("Insert payment amount: ");
        else
            return -1; // Signal cancellation
    }

    return payment;
}

void Store::completeCheckout(Client *client, double payment, double total)
{
    clearConsole();

    // Apply gambling only for registered clients
    if (client && client->getClientId() != 0)
    {
        Store::gambling(cart, 25);
    }

    // Create receipt with appropriate client ID
    int clientId = client ? client->getClientId() : 0;
    Receipt receipt(cart, payment, clientId);

    cout << receipt.toDisplay();

    // Update stock and clear cart
    updateStockFromShelf();
    clearCart();

    pause();
}

void Store::gambling(vector<CartItem> &sale, int chance)
{
    srand(time(0));
    int badLuck = (rand() % 101); // badluck goes from 0 to 100

    if (badLuck < chance) // if the "bad luck" is less than the chance, win
    {
        // vector<CartItem> roster = sale;

        srand(time(0));                         // reinitializing seed
        int sortedIndex = rand() % sale.size(); // randomizing index

        CartItem jackpot = sale.at(sortedIndex);
        cout << "You won a free " << jackpot.getProductName() << "!" << endl;
        jackpot.setQuantity(1); // client only gets one, >:(

        double fullPrice = jackpot.getSaleWithoutTax();
        // jackpot.setTaxRatePercent(0);        // Disable tax (don't apply again)
        jackpot.setSaleWithoutTax(-fullPrice); // Negate full price (as base)

        sale.push_back(jackpot); // item gets added at end of receipt for display
    }
}