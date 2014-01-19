#include "albumitem.h"

/** Create a new instance of AlbumItem. The instance will be initialized with
 *  values coming from a list of keys-values.
 *  Keys :
 *      - id
 *      - artist
 *      - year
 *      - artwork_track_id
 *      - artist_id
 *      - album */
AlbumItem::AlbumItem(LmsConnector* connector, QMap<QString, QString> tokens) : RessourceItem(connector, "")
{
    type = RessourceItem::Album;

    if(tokens.contains("id"))
        this->id = tokens["id"].toInt();
    if(tokens.contains("artist"))
        this->artistName = tokens["artist"];
    if(tokens.contains("year"))
        this->year = tokens["year"].toInt();
    if(tokens.contains("artwork_track_id"))
        this->coverId = tokens["artwork_track_id"];
    if(tokens.contains("artist_id"))
        this->artistId = tokens["artist_id"].toInt();
    if(tokens.contains("album"))
        this->name = tokens["album"];
}

void AlbumItem::FillSubItems()
{
    QList<TrackItem*> list = connector->GetTrackCollection(this->id);
    for(int i = 0; i < list.count(); i++)
    {
        this->AddItem((RessourceItem*)list[i]);
    }
}

QString AlbumItem::GetCoverUrl()
{
    if(this->coverId == QString::null)
        return connector->GetUnknownCoverUrl();
    else
        return connector->GetCoverUrl(this->coverId);
}

int AlbumItem::GetYear()
{
    return this->year;
}

QString AlbumItem::GetArtistName()
{
    return this->artistName;
}

void AlbumItem::SetYear(int year)
{
    this->year = year;
}

void AlbumItem::SetArtistName(QString artist)
{
    this->artistName = artist;
}

void AlbumItem::Play()
{
    this->connector->PlayAlbum(this->id);
}


