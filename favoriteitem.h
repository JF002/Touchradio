#ifndef FAVORITEITEM_H
#define FAVORITEITEM_H

#include "lmsconnector.h"

class FavoriteItem : public RessourceItem
{
    Q_OBJECT
    Q_PROPERTY(QString url READ GetUrl NOTIFY UrlChanged)
    Q_PROPERTY(QString coverUrl READ GetCoverUrl NOTIFY CoverUrlChanged)
public:
    FavoriteItem();
    FavoriteItem(LMSConnector* connector, const QString& favoriteName, const QString& favoriteId);
    FavoriteItem(LMSConnector* connector, QMap<QString, QString> tokens);

    RessourceItem::ItemTypes GetItemType();
    void Play();

    QString GetUrl();
    void SetUrl(QString url);

    QString GetCoverUrl();
    void SetCoverUrl(QString coverUrl);


Q_SIGNALS:
    void UrlChanged();
    void CoverUrlChanged();

private:
    QString m_favoriteId;
    LMSConnector* m_connector;
    QString m_url;
};

#endif // FAVORITEITEM_H
