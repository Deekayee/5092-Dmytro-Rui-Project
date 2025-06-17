#include "../include/menu.h"

#include <iostream>
#include <regex>
#include <iomanip>

void Menu::pause() // pause the console
{
    cout << "Press enter to continue...";
    cin.ignore();
}

void Menu::limh(int n) // horizontal line with color
{
    cout << Magenta << string(n, '-') << RESET << endl;
}

void Menu::clearConsole() // clear the console
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}

string Menu::stringToLower(string name)
{
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    return lowerName;
}

// default prompt -> "Do you wish to continue?"
// prints as -> "Do you wish to continue (y̲/n)?"
bool Menu::promptYESOrNo(string prompt)
{
    string input;
    while (true)
    {
        cout << prompt << " (" << UNDERLINE << "y" << RESET << "/n): ";
        getline(cin, input);
        input = stringToLower(input);

        if (input == "y" || input.empty())
            return true;
        else if (input == "n")
            return false;
        else
            cout << "Invalid input. Please enter 'y' or 'n' or press enter for default." << endl;
    }
}

// default prompt -> "Do you wish to continue?"
// prints as -> "Do you wish to continue (y/n̲)?"
bool Menu::promptyesOrNO(string prompt)
{
    string input;
    while (true)
    {
        cout << prompt << " (y/" << UNDERLINE << "n" << RESET << "): ";
        getline(cin, input);
        input = stringToLower(input);

        if (input == "n" || input.empty())
            return false;
        else if (input == "y")
            return true;
        else
            cout << "Invalid input. Please enter 'y' or 'n' or press enter for default." << endl;
    }
}

// returns true if number is validated, false if not
bool Menu::validateMenuInput(const string &input, int &opt)
{
    // Check if the string is entirely digits
    for (char ch : input)
    {
        if (!isdigit(ch))
        {
            cout << "Please enter a number" << endl;
            pause();
            return false;
        }
    }

    // catch exceptions
    try
    {
        opt = stoi(input);
    }
    catch (const std::out_of_range &)
    {
        cout << "Number is too large. Please enter a smaller number." << endl;
        pause();
        return false;
    }
    catch (const std::invalid_argument &)
    {
        cout << "Invalid input. Please enter numbers only." << endl;
        pause();
        return false;
    }
    return true;
}

int Menu::getValidatedInt(const string &prompt, bool zero)
{
    string input;
    int value;
    regex pattern("^\\d+$"); // Matches only positive integers (no minus sign, no letters)

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (!regex_match(input, pattern))
        {
            cout << "Invalid input. Please enter a positive whole number." << endl;
            continue;
        }
        try
        {
            value = stoi(input);
            if (value == 0 && zero == false)
            {
                cout << "Value must be greater than zero." << endl;
                continue;
            }
            return value;
        }
        catch (...)
        {
            cout << "Number is out of range. Try a smaller value." << endl;
        }
    }
}

double Menu::getValidatedDouble(const string &prompt)
{
    const double maxValue = 1000000.00; // Arbitrary maximum
    string input;
    double value;
    regex pattern("^\\d+(\\.\\d{1,2})?$"); // Matches only positive integers with up to two decimal places

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (!regex_match(input, pattern))
        {
            cout << "Invalid input. Please enter a positive number with up to two decimals." << endl;
            continue;
        }
        try
        {
            value = stod(input);
            if (value <= 0.0)
            {
                cout << "Value must be greater than zero." << endl;
                continue;
            }
            if (value > maxValue)
            {
                cout << "Value exceeds allowed maximum of €" << fixed << setprecision(2) << maxValue << "." << endl;
                continue;
            }
            return value;
        }
        catch (...)
        {
            cout << "Number is out of range. Try a smaller value." << endl;
        }
    }
}

void Menu::setColor(const string &colorCode)
{
    cout << colorCode;
}