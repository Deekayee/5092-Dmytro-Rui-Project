#pragma once //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "utils.h"

void salesMenu(vector<Stock> &stockList, vector<Stock> &shelf, vector<CartItem> &cart); // TODO
void printCart(vector<CartItem> &cart);
CartItem *findItemCart(vector<CartItem> &cart, int id, int *index = nullptr);

void addProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
void removeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
void changeProductCart(vector<Stock> &shelf, vector<CartItem> &cart, bool menuState);
void clearCart(vector<Stock> &shelf, vector<CartItem> &cart);

void checkout(vector<Stock> &stockList, vector<CartItem> &cart);
