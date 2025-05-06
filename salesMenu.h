#pragma once //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "utils.h"

void salesMenu(vector <Stock> &stockList, vector <CartItem> &cart); // TODO
    void addProductCart(vector<Stock> &stockList, vector<CartItem> &cart, bool menuState);
void printCart(vector<Stock> &stockList, vector<CartItem> &cart); // TODO