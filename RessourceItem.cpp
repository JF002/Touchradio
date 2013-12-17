#include <QHash>

#include "RessourceItem.h"

RessourceItem::RessourceItem(QObject* parent)
{
    this->m_title = "";
    this->m_id = 0;
    this->m_type = Node;
    this->m_parentItem = NULL;
    this->m_cover = QString::null;
}

RessourceItem::RessourceItem(RessourceItem* parentItem, const QString title)
{
    m_parentItem = parentItem;
    this->m_title = title;
    this->m_id = 0;
    this->m_type = Node;
    this->m_cover = QString::null;
}

RessourceItem::RessourceItem(const QString title)
{
    this->m_title = title;
    this->m_id = 0;
    this->m_type = Node;
    this->m_parentItem = NULL;
    this->m_cover = QString::null;
}

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

void RessourceItem::SetTitle(QString title)
{
    m_title = title;
}
QString RessourceItem::GetTitle()
{
    return m_title;
}

void RessourceItem::AddItem(RessourceItem* item)
{
    item->SetId(children.count());
    item->SetParentItem(this);
    children << item;
}

void RessourceItem::SetId(int id)
{
    m_id = id;
}

QString RessourceItem::GetCoverUrl()
{
    return m_cover;
}

void RessourceItem::SetParentItem(RessourceItem* parentItem)
{
    this->m_parentItem = parentItem;
}

RessourceItem* RessourceItem::GetParentItem()
{
    return m_parentItem;
}

QHash<int, QByteArray> RessourceItem::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[IdRole] = "id";
    return roles;
}

int RessourceItem::GetId()
{
    return m_id;
}

QString RessourceItem::toString() const
 {
     return m_title;
 }

RessourceItem::ItemTypes RessourceItem::GetItemType()
{
    return m_type;
}


