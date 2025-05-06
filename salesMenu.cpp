#include "salesMenu.h"


using namespace std;


// Sales Menu
<<<<<<< HEAD
void salesMenu(vector <Stock> &stockList, vector <CartItem> &cart)
=======
void salesMenu()
>>>>>>> e721a0d3870264362d948158f1876a54a753344f
{
    bool salesMenu = true;
    string input;
    int salesOpt;
    do
    {
        do
        {
<<<<<<< HEAD
            
            
            limh();
            cout << "Options:" << endl
                 << "1. Add product to cart" << endl
                 << "2. View Cart" << endl;
            cout << "Option: ";

=======
            clearConsole();
            setColor("\033[0;36m");
            cout << "Sales Menu" << endl;
            setColor("\033[0m");
            limh();
            cout << "1. Show Products" << endl;
            limh();
            cout << "2. Go Back" << endl;
            limh();
            cout << "Option: ";
>>>>>>> e721a0d3870264362d948158f1876a54a753344f
            getline(cin, input);
        } while (!validateMenuInput(input, salesOpt));

        switch (salesOpt)
        {
        case 1:
<<<<<<< HEAD
=======
            cout << "Products" << endl;
            limh();
            // show products
>>>>>>> e721a0d3870264362d948158f1876a54a753344f
            productsMenu();
            break;
        case 2:
            salesMenu = false;
            break;
        default:
            cout << "Invalid input, try again." << endl;
            pause();
            break;
        }

    } while (salesMenu);
}

// Products Menu
<<<<<<< HEAD
int productsMenu() // TODO
=======
void productsMenu() // TODO
>>>>>>> e721a0d3870264362d948158f1876a54a753344f
{
    bool productsMenu = true;
    int productsOpt;
    do
    {
<<<<<<< HEAD
=======
        clearConsole();
>>>>>>> e721a0d3870264362d948158f1876a54a753344f

        // function to show products as selectable options, when selected, show more details and give option to add to cart (input quantity here), checkout or cancel
        cout << "Products" << endl;
        limh();

        /*Show products here*/

        cin >> productsOpt;
        cout << endl
             << "Press 0 to go cancel" << endl; // placeholder
        cin.ignore();

        if (productsOpt == 0)
            productsMenu = false;

    } while (productsMenu);
}