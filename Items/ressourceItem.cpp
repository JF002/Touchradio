#include <QHash>

#include "ressourceItem.h"

/** Create a new instance of RessourceItem, specifying the parent item and the name. */
RessourceItem::RessourceItem(LmsConnector* connector, RessourceItem* parentItem, const QString name) : QObject(NULL)
{
    this->parentItem = parentItem;
    this->name = name;
    this->id = 0;
    this->type = Node;
    this->coverUrl = QString::null;
    this->connector = connector;
}

/** Create a new instance of RessourceItem, specifying the name. Parent is set to NULL. */
RessourceItem::RessourceItem(LmsConnector* connector, const QString name) : QObject(NULL)
{
    this->name = name;
    this->id = 0;
    this->type = Node;
    this->parentItem = NULL;
    this->coverUrl = QString::null;
    this->connector = connector;
}

/** Set the ID of the instance. The ID is a unique identifier */
void RessourceItem::SetId(int id)
{
    this->id = id;
}

/** Return the ID of the instance. The ID is a unique identifier */
int RessourceItem::GetId()
{
    return this->id;
}

/** Set the name */
void RessourceItem::SetName(QString name)
{
    this->name = name;
}

/** Return the name */
QString RessourceItem::GetName()
{
    return this->name;
}

/** Return the parent item of this item */
RessourceItem* RessourceItem::GetParentItem()
{
    return this->parentItem;
}

void RessourceItem::SetParentItem(RessourceItem* parentItem)
{
    this->parentItem = parentItem;
}

/** Return the list of sub-items of this instance. */
QList<RessourceItem*> RessourceItem::GetSubItems()
{
    if(children.count() == 0)
    {
        FillSubItems();
    }

    return children;
}

void RessourceItem::FillSubItems()
{

}

RessourceItem::ItemTypes RessourceItem::GetItemType()
{
    return type;
}

void RessourceItem::AddItem(RessourceItem* item)
{
    item->SetParentItem(this);
    this->children << item;
}

QString RessourceItem::GetCoverUrl()
{
    return this->coverUrl;
}


