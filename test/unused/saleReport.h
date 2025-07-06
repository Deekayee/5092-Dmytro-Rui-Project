#pragma once

#include "productReport.h"
#include <vector>


class Receipt
{
    int idCliente;
    vector <ProductReport> products;

public:
    int getClientId();
    ProductReport* findProductId(int id);
    
};