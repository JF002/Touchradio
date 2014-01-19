#ifndef FAVORITEITEM_H
#define FAVORITEITEM_H

#include "ressourceItem.h"

class FavoriteItem : public RessourceItem
{
    Q_OBJECT
    Q_PROPERTY(QString url READ GetUrl NOTIFY UrlChanged)
public:
    FavoriteItem(LmsConnector* connector, QMap<QString, QString> tokens);

    QString GetUrl();
    void SetUrl(QString url);

    virtual QString GetCoverUrl();

public slots:
    void Play();

Q_SIGNALS:
    void UrlChanged();

protected:
    virtual void FillSubItems();

private:
    QString url;
    QString favoriteId; // Do not use ID from base class as favorites needs a string to store the ID
};

#endif // FAVORITEITEM_H
