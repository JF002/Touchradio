#ifndef ALBUMITEM_H
#define ALBUMITEM_H

#include "lmsconnector.h"
#include "ressourceItem.h"

class LmsConnector;

class AlbumItem : public RessourceItem
{
    Q_OBJECT
    Q_PROPERTY(QString albumTitle READ GetAlbumTitle NOTIFY AlbumTitleChanged)
    Q_PROPERTY(int year READ GetYear NOTIFY YearChanged)
    Q_PROPERTY(double duration READ GetDuration NOTIFY DurationChanged)
    Q_PROPERTY(QString artist READ GetArtistName NOTIFY ArtistChanged)
public:
    AlbumItem();
    AlbumItem(LmsConnector* connector, int artistId, const QString albumName, int albumId);
    AlbumItem(LmsConnector* connector, QMap<QString, QString> tokens);

    int GetAlbumId();
    int GetArtistId();

    QString GetAlbumTitle();
    int GetYear();
    double GetDuration();
    virtual QString GetCoverUrl();
    QString GetArtistName();

    void SetAlbumTitle(QString title);
    void SetYear(int year);
    void SetDuration(double duration);
    void SetCoverId(QString coverid);
    void SetArtistName(QString artist);

Q_SIGNALS:
    void AlbumTitleChanged();
    void YearChanged();
    void DurationChanged();
    void ArtistChanged();

public slots:
    QString toString() const;
    void Play();

protected:
    virtual void FillSubItems();
    void GetDetailedInfo();

private:
    QString m_albumName;
    int m_artistId;
    int m_albumId;
    LmsConnector* connector;
    int m_year;
    double m_duration;
    QString m_coverId;
    bool detailsInfoFilled;
    QString m_artistName;

};

#endif // ALBUMITEM_H
