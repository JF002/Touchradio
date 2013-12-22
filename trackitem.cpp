#include "trackitem.h"

TrackItem::TrackItem()
{
    m_albumId = 0;
    m_trackId = 0;
    m_trackNum = 0;
    m_trackName = "";
    connector = NULL;
    this->m_type = Track;
    detailsInfoFilled = false;
    m_coverId = QString::null;
}

TrackItem::TrackItem(LMSConnector* connector, int albumId, int trackNum, const QString trackName, int trackId): RessourceItem(trackName)
{
    m_albumId = albumId;
    m_trackId = trackId;
    m_trackName = trackName;
    m_trackNum = trackNum;
    this->connector = connector;
    this->m_type = Track;
    detailsInfoFilled = false;
    m_coverId = QString::null;
}


QString TrackItem::toString() const
 {
    return QString(m_albumId) + "-" + QString(m_trackId) + "-" + m_trackName;
 }

int TrackItem::GetAlbumId()
{
    return m_albumId;
}

int TrackItem::GetTrackId()
{
    return m_trackId;
}

QString TrackItem::GetTrackTitle()
{
    GetDetailedInfo();
    return m_trackName;
}

QString TrackItem::GetArtistName()
{
    GetDetailedInfo();
    return m_artistName;
}

QString TrackItem::GetCoverUrl()
{
    GetDetailedInfo();
    if(m_coverId == QString::null)
        return connector->GetUnknownCoverUrl();
    else
        return connector->GetCoverUrl(m_coverId);
}

double TrackItem::GetDuration()
{
    GetDetailedInfo();
    return m_duration;
}

QString TrackItem::GetAlbumName()
{
    GetDetailedInfo();
    return m_albumName;
}

int TrackItem::GetYear()
{
    GetDetailedInfo();
    return m_year;
}

void TrackItem::SetArtistName(QString artist)
{
    m_artistName = artist;
}

void TrackItem::SetCoverId(QString coverId)
{
    m_coverId = coverId;
}

void TrackItem::SetAlbumName(QString albumName)
{
    m_albumName = albumName;
}

void TrackItem::SetYear(int year)
{
    m_year = year;
}

void TrackItem::SetDuration(double duration)
{
    m_duration = duration;
}

void TrackItem::FillSubItems()
{

}

void TrackItem::Play()
{
    this->connector->Play(m_trackId, m_albumId, m_trackNum);
}

void TrackItem::GetDetailedInfo()
{
    /*
    if(!detailsInfoFilled)
    {
        this->connector->FillTrackInfo(this);
        detailsInfoFilled = true;
    }
    */
}

