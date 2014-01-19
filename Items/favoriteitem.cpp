#include "favoriteitem.h"

/** Create a new instance of FavoriteItem. The instance will be initialized with
 *  values coming from a list of keys-values.
 *  Keys :
 *      - id
 *      - name
 *      - url */
FavoriteItem::FavoriteItem(LmsConnector* connector, QMap<QString, QString> tokens) : RessourceItem(connector, "")
{
    this->type = RessourceItem::Favorite;

    if(tokens.contains("id"))
        this->favoriteId = tokens["id"];
    if(tokens.contains("name"))
        this->name = tokens["name"];
    if(tokens.contains("url"))
        this->url = tokens["url"];
}

void FavoriteItem::Play()
{
    this->connector->PlayFavorite(this->favoriteId);
}

QString FavoriteItem::GetUrl()
{
    return this->url;
}

void FavoriteItem::SetUrl(QString url)
{
    this->url = url;
}

QString FavoriteItem::GetCoverUrl()
{
    return this->connector->GetRadioCoverUrl();
}

void FavoriteItem::FillSubItems()
{
    // Nothing to do, Favorite do not have subitems
}

