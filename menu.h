#pragma once //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "utils.h"

void mainMenu(vector<Stock> &stockList);
void salesMenu(); //TODO
void productsMenu(); //TODO
void stockMenu(vector<Stock> &stockList);
void editStockMenu(vector<Stock> &stockList);
void searchEditMenu(vector<Stock> &stockList);
void changeEditMenu(vector<Stock> &stockList);