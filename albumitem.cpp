#include "albumitem.h"

AlbumItem::AlbumItem()
{
    m_albumName = "";
    m_artistId = 0;
    m_albumId = 0;
    this->m_type = Album;
    detailsInfoFilled = false;
}

AlbumItem::AlbumItem(LMSConnector* connector, int artistId, const QString albumName, int albumId) : RessourceItem(albumName)
{
    this->m_albumName = m_title = albumName;
    this->m_artistId = artistId;
    this->m_albumId = albumId;
    this->connector = connector;
    this->m_type = Album;
    detailsInfoFilled = false;
}

QString AlbumItem::toString() const
 {
    return QString(m_artistId) + "-" + QString(m_albumId) + "-" + m_albumName;
 }

int AlbumItem::GetArtistId()
{
    return m_artistId;
}

int AlbumItem::GetAlbumId()
{
    return m_albumId;
}

QString AlbumItem::GetAlbumTitle()
{
    return m_albumName;
}

int AlbumItem::GetYear()
{
    return m_year;
}

double AlbumItem::GetDuration()
{
    return m_duration;
}

QString AlbumItem::GetArtistName()
{
    return m_artistName;
}

QString AlbumItem::GetCoverUrl()
{
    if(m_coverId == QString::null)
        return connector->GetUnknownCoverUrl();
    else
        return connector->GetCoverUrl(m_coverId);
}

void AlbumItem::SetAlbumTitle(QString title)
{
    m_albumName = title;
}

void AlbumItem::SetYear(int year)
{
    m_year = year;
}

void AlbumItem::SetDuration(double duration)
{
    m_duration = duration;
}

void AlbumItem::SetCoverId(QString coverid)
{
    m_coverId = coverid;
}

void AlbumItem::SetArtistName(QString artist)
{
    m_artistName = artist;
}

void AlbumItem::FillSubItems()
{
    QList<TrackItem*> list = connector->GetTrackCollection(GetAlbumId());
    for(int i = 0; i < list.count(); i++)
    {
        this->AddItem(list[i]);
    }
}

void AlbumItem::Play()
{
    this->connector->PlayAlbum(m_albumId);
}

