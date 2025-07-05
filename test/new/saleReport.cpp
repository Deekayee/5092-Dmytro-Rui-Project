#include "saleReport.h"

using namespace std;

int SaleReport::getClientId() {return idCliente;}

ProductReport *SaleReport::findProductId(int id)
{
    for(ProductReport &tmp : products )
    {
        if (id == tmp.getId())
            return &tmp;
    }
    return nullptr;
}