#pragma once //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <random>
#include "utils.h"

void salesMenu(vector<Stock> &stockList, vector<Stock> &shelf, vector<CartItem> &cart);

void addProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
void removeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
void changeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
void clearCart(vector<CartItem> &cart, vector<Stock> *shelf = nullptr);

void checkoutMenu(vector<Stock> &stockList, vector<Stock> &shelf, vector<CartItem> &cart);
void gambling(vector<CartItem> &sale, int chance = 50);
bool login();
bool registerLogin();
