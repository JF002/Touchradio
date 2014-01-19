#include "trackitem.h"

/** Create a new instance of TrackItem. The instance will be initialized with
 *  values coming from a list of keys-values.
 *  Keys :
 *      - id
 *      - title
 *      - artist
 *      - album_id
 *      - album
 *      - duration
 *      - tracknum
 *      - year
 *      - coverrid */
TrackItem::TrackItem(LmsConnector* connector, QMap<QString, QString> tokens) : RessourceItem(connector, "")
{
    this->type = Track;

    if(tokens.contains("id"))
        this->id = tokens["id"].toInt();
    if(tokens.contains("title"))
        this->name = tokens["title"];
    if(tokens.contains("artist"))
        this->artistName = tokens["artist"];
    if(tokens.contains("album_id"))
        this->albumId = tokens["album_id"].toInt();
    if(tokens.contains("album"))
        this->albumName = tokens["album"];
    if(tokens.contains("duration"))
        this->duration = tokens["duration"].toDouble();
    if(tokens.contains("tracknum"))
        this->trackNum = tokens["tracknum"].toInt();
    if(tokens.contains("year"))
        this->year = tokens["year"].toInt();
    if(tokens.contains("coverid"))
        this->coverId = tokens["coverid"];
}

QString TrackItem::GetArtistName()
{
    return this->artistName;
}

double TrackItem::GetDuration()
{
    return this->duration;
}

QString TrackItem::GetAlbumName()
{
    return this->albumName;
}

int TrackItem::GetYear()
{
    return this->year;
}

void TrackItem::SetArtistName(QString name)
{
    this->artistName = name;
}

void TrackItem::SetDuration(double duration)
{
    this->duration = duration;
}

void TrackItem::SetAlbumName(QString name)
{
    this->albumName = name;
}

void TrackItem::SetYear(int year)
{
    this->year = year;
}

QString TrackItem::GetCoverUrl()
{
    if(this->coverId == QString::null)
        return connector->GetUnknownCoverUrl();
    else
        return connector->GetCoverUrl(this->coverId);
}

void TrackItem::Play()
{
    this->connector->Play(this->id, this->albumId, this->trackNum);
}

