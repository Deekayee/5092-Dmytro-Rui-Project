#pragma once

#include "productReport.h"
#include <vector>


class SaleReport
{
    int idCliente;
    vector <ProductReport> products;

public:
    int getClientId();
    ProductReport* findProductId(int id);
    
};