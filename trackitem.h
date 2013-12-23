#ifndef TRACKITEM_H
#define TRACKITEM_H

#include "lmsconnector.h"
#include "RessourceItem.h"

class LMSConnector;


class TrackItem : public RessourceItem
{
    Q_OBJECT
    Q_PROPERTY(QString trackTitle READ GetTrackTitle NOTIFY TrackTitleChanged)
    Q_PROPERTY(QString artistName READ GetArtistName WRITE SetArtistName NOTIFY ArtistNameChanged)

    Q_PROPERTY(double duration READ GetDuration WRITE SetDuration NOTIFY DurationChanged)
    Q_PROPERTY(QString albumName READ GetAlbumName WRITE SetAlbumName NOTIFY AlbumNameChanged)
    Q_PROPERTY(int year READ GetYear WRITE SetYear NOTIFY YearChanged)
public:
    TrackItem();
    TrackItem(LMSConnector* connector, int albumId, int tracknum, const QString trackName, int trackId);
    TrackItem(LMSConnector* connector, QMap<QString, QString> tokens);
    int GetAlbumId();
    int GetTrackId();
    QString GetTrackTitle();

    QString GetArtistName();
    virtual QString GetCoverUrl();
    double GetDuration();
    QString GetAlbumName();
    int GetYear();

    void SetArtistName(QString artist);
    void SetCoverId(QString coverId);
    void SetDuration(double duration);
    void SetAlbumName(QString album);
    void SetYear(int year);

    void Play();

Q_SIGNALS:
    void TrackTitleChanged();
    void ArtistNameChanged();
    void DurationChanged();
    void AlbumNameChanged();
    void YearChanged();

public slots:
    QString toString() const;

protected:
    LMSConnector* connector;
    virtual void FillSubItems();
    void GetDetailedInfo();

private:
    int m_albumId;
    int m_trackId;
    int m_trackNum;
    QString m_trackName;
    double m_duration;
    int m_year;
    QString m_albumName;
    QString m_artistName;
    QString m_coverId;

    bool detailsInfoFilled;
};

#endif // TRACKITEM_H
