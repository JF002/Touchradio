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
    FavoriteItem(LmsConnector* connector, const QString& favoriteName, const QString& favoriteId);
    FavoriteItem(LmsConnector* connector, QMap<QString, QString> tokens);

    RessourceItem::ItemTypes GetItemType();


    QString GetUrl();
    void SetUrl(QString url);

    QString GetCoverUrl();

public slots:
    void Play();

Q_SIGNALS:
    void UrlChanged();
    void CoverUrlChanged();

private:
    QString m_favoriteId;
    LmsConnector* m_connector;
    QString m_url;
};

#endif // FAVORITEITEM_H
