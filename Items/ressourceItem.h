#ifndef RESSOURCEITEM_H
#define RESSOURCEITEM_H

#include <QObject>
#include <QTextStream>
#include "lmsconnector.h"

class RessourceItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ GetName WRITE SetName NOTIFY NameChanged)
    Q_PROPERTY(int type READ GetItemType NOTIFY TypeChanged)
    Q_PROPERTY(QString coverUrl READ GetCoverUrl NOTIFY CoverUrlChanged)
public:
    RessourceItem(LmsConnector* connector, RessourceItem* parentItem, const QString title);
    RessourceItem(LmsConnector* connector, const QString title);

    enum ItemTypes {
        Node,
        Artist,
        Album,
        Track,
        Favorite
    };

    void AddItem(RessourceItem* item);
    QList<RessourceItem*> GetSubItems();

    int GetId();
    void SetId(const int id);

    void SetName(QString name);
    QString GetName();

    RessourceItem* GetParentItem();
    void SetParentItem(RessourceItem*);

    ItemTypes GetItemType();

    virtual QString GetCoverUrl();

Q_SIGNALS:
    void NameChanged();
    void TypeChanged();
    void CoverUrlChanged();

protected:
    QList<RessourceItem*> children;
    RessourceItem* parentItem;
    virtual void FillSubItems();
    LmsConnector* connector;

    QString name;
    ItemTypes type;
    QString coverUrl;
    int id;
};


#endif // RESSOURCEITEM_H

