#include "favoriteitem.h"

FavoriteItem::FavoriteItem() : RessourceItem("")
{
    m_favoriteId= "";
    m_type = RessourceItem::Favorite;
}


FavoriteItem::FavoriteItem(LMSConnector* connector, const QString& favoriteName, const QString& favoriteId) : RessourceItem(favoriteName)
{
    m_favoriteId = favoriteId;
    m_connector = connector;
    m_type = RessourceItem::Favorite;
}

RessourceItem::ItemTypes FavoriteItem::GetItemType()
{
    return m_type;
}


void FavoriteItem::Play()
{
    this->m_connector->PlayFavorite(m_favoriteId);
}

QString FavoriteItem::GetUrl()
{
    return m_url;
}

void FavoriteItem::SetUrl(QString url)
{
    m_url = url;
}

QString FavoriteItem::GetCoverUrl()
{
    return m_connector->GetRadioCoverUrl();
}

void FavoriteItem::SetCoverUrl(QString coverUrl)
{

}
