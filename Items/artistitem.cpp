#include "artistitem.h"

ArtistItem::ArtistItem() : RessourceItem("")
{
    m_artistId = 0;
    connector = NULL;
    this->m_type = Artist;
}

ArtistItem::ArtistItem(LmsConnector* connector, const QString artistName, int artistId) : RessourceItem(artistName)
{
    m_artistId = artistId;
    this->connector = connector;
    this->m_type = Artist;
}

ArtistItem::ArtistItem(LmsConnector* connector, QMap<QString, QString> tokens) : RessourceItem("")
{
    this->connector = connector;
    m_type = RessourceItem::Artist;

    if(tokens.contains("id"))
    {
        this->m_artistId = tokens["id"].toInt();
    }
    if(tokens.contains("artist"))
        this->m_title = tokens["artist"];
}

QString ArtistItem::toString() const
 {
    return m_artistId + "-" + m_title;
 }

int ArtistItem::GetArtistId()
{
    return m_artistId;
}

void ArtistItem::FillSubItems()
{
    QList<AlbumItem*> albumCollection = connector->GetAlbumCollection(GetArtistId());
    for(int i = 0; i < albumCollection.count(); i++)
    {
        this->AddItem(albumCollection[i]);
    }
}
