#ifndef RESSOURCEITEM_H
#define RESSOURCEITEM_H

#include <QObject>
#include <QTextStream>

class RessourceItem: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ GetTitle WRITE SetTitle NOTIFY TitleChanged)
    Q_PROPERTY(int id READ GetId WRITE SetId NOTIFY IdChanged)
    Q_PROPERTY(int type READ GetItemType NOTIFY TypeChanged)
    Q_PROPERTY(QString coverUrl READ GetCoverUrl NOTIFY CoverUrlChanged)
public:
    RessourceItem(RessourceItem* parentItem, const QString title);
    RessourceItem(const QString title);
    RessourceItem(QObject* parent = 0);

    enum RessourceItemRoles {
            TitleRole = Qt::UserRole + 1,
            IdRole
        };

    enum ItemTypes {
        Node,
        Artist,
        Album,
        Track,
        Favorite
    };

    void AddItem(RessourceItem* item);

    void SetTitle(QString title);
    void SetId(const int id);

    QString GetTitle();
    virtual QString GetCoverUrl();
    int GetId();
    ItemTypes GetItemType();

    RessourceItem* GetParentItem();
    QList<RessourceItem*> GetSubItems();
    void SetParentItem(RessourceItem*);

Q_SIGNALS:
    void TitleChanged();
    void IdChanged();
    void TypeChanged();
    void CoverUrlChanged();

public slots:
    QString toString() const;

protected:
    virtual void FillSubItems();
    QHash<int, QByteArray> roleNames() const;
    QString m_title;
    QList<RessourceItem*> children;
    ItemTypes m_type;
    QString m_cover;

private:
    RessourceItem* m_parentItem;



    int m_id;

};

#endif // RESSOURCEITEM_H

