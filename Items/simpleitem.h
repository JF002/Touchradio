#ifndef SIMPLEITEM_H
#define SIMPLEITEM_H
#include <QString>
#include "ressourceItem.h"

class SimpleItem : public RessourceItem
{
public:
    SimpleItem(QString name);

protected:
    virtual void FillSubItems();
};

#endif // SIMPLEITEM_H
