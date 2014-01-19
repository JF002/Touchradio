#ifndef ALBUMITEM_H
#define ALBUMITEM_H

#include "ressourceItem.h"


class AlbumItem : public RessourceItem
{
    Q_OBJECT
    Q_PROPERTY(int year READ GetYear NOTIFY YearChanged)
    Q_PROPERTY(QString artist READ GetArtistName NOTIFY ArtistChanged)
public:
    AlbumItem(LmsConnector* connector, QMap<QString, QString> tokens);

    int GetYear();
    QString GetArtistName();

    void SetYear(int year);
    void SetArtistName(QString artist);

    virtual QString GetCoverUrl();

public slots:
    void Play();

Q_SIGNALS:
    void YearChanged();
    void DurationChanged();
    void ArtistChanged();

private:
    virtual void FillSubItems();

    QString artistName;
    int year;
    QString coverId;
    int artistId;

};

#endif // ALBUMITEM_H
