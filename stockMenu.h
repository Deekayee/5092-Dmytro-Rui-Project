#pragma once //  compiler only sees this lib file once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "utils.h"


void stockMenu(vector<Stock> &stockList);
    void editStockMenu(vector<Stock> &stockList);
        void searchEditMenu(vector<Stock> &stockList);
        void changeEditMenu(vector<Stock> &stockList);
        void removeEditMenu(vector<Stock> &stockList);