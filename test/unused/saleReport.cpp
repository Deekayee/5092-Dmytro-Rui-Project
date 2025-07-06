#include "saleReport.h"

using namespace std;

int Receipt::getClientId() {return idCliente;}

ProductReport *Receipt::findProductId(int id)
{
    for(ProductReport &tmp : products )
    {
        if (id == tmp.getId())
            return &tmp;
    }
    return nullptr;
}