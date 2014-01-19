
#ifndef QOBJECTLISTMODEL_H
#define QOBJECTLISTMODEL_H

#include <QAbstractListModel>
#include "ressourceItem.h"

/*
    Open issues:
        object ownership: is it helpful for the model to own the objects?
                          can we guard the objects so they are automatically removed
                              from the model when deleted?
        add additional QList convenience functions (operator<<, etc.)
*/

class QObjectListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString currentItemName READ GetCurrentItemName NOTIFY currentItemNameChanged)
public:
    explicit QObjectListModel(QObject *parent = 0);
    QObjectListModel(QObjectList objects, QObject *parent = 0);

    //model API
    enum Roles { ObjectRole = Qt::UserRole+1 };



    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QObjectList objectList() const;
    void setObjectList(QObjectList objects);

    //list API
    void append(QObject *object);
    void append(const QObjectList &objects);
    void insert(int i, QObject *object);
    void insert(int i, const QObjectList &objects);

    inline QObject *at(int i) const { return m_objects.at(i); }
    inline QObject *operator[](int i) const { return m_objects[i]; }
    void replace(int i, QObject *object);

    void move(int from, int to);

    void removeAt(int i, int count = 1);
    QObject *takeAt(int i);
    void clear();

    inline bool contains(QObject *object) const { return m_objects.contains(object); }
    inline int indexOf (QObject *object, int from = 0) const { return m_objects.indexOf(object, from); }
    inline int lastIndexOf (QObject *object, int from = -1) const { return m_objects.lastIndexOf(object, from); }

    inline int count() const { return m_objects.count(); }
    inline int size() const { return m_objects.size(); }
    inline bool isEmpty() const { return m_objects.isEmpty(); }

    QString GetCurrentItemName();

    //additional QML API
    Q_INVOKABLE QObject *get(int i) const;

Q_SIGNALS:
    void countChanged();
    void currentItemNameChanged();

public slots:
    void goToSubItems(RessourceItem* item);
    void back();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    Q_DISABLE_COPY(QObjectListModel)
    QObjectList m_objects;
    RessourceItem* currentItem;
};

#endif // QOBJECTMODEL_H
