#ifndef TRACKITEM_H
#define TRACKITEM_H

#include "ressourceItem.h"

class TrackItem : public RessourceItem
{
    Q_OBJECT
    Q_PROPERTY(QString artistName READ GetArtistName WRITE SetArtistName NOTIFY ArtistNameChanged)
    Q_PROPERTY(double duration READ GetDuration WRITE SetDuration NOTIFY DurationChanged)
    Q_PROPERTY(QString albumName READ GetAlbumName WRITE SetAlbumName NOTIFY AlbumNameChanged)
    Q_PROPERTY(int year READ GetYear WRITE SetYear NOTIFY YearChanged)
public:
     TrackItem(LmsConnector* connector, QMap<QString, QString> tokens);

     QString GetArtistName();
     double GetDuration();
     QString GetAlbumName();
     int GetYear();

     void SetArtistName(QString name);
     void SetDuration(double duration);
     void SetAlbumName(QString name);
     void SetYear(int year);

     virtual QString GetCoverUrl();

public slots:
     void Play();

Q_SIGNALS:
    void ArtistNameChanged();
    void DurationChanged();
    void AlbumNameChanged();
    void YearChanged();

protected:
    virtual void FillSubItems();

private:
     QString artistName;
     int albumId;
     QString albumName;
     double duration;
     int trackNum;
     int year;
     QString coverId;
};

#endif // TRACKITEM_H
