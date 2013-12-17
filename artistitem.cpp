#include "artistitem.h"

ArtistItem::ArtistItem() : RessourceItem("")
{
    m_artistId = 0;
    connector = NULL;
    this->m_type = Artist;
}

ArtistItem::ArtistItem(LMSConnector* connector, const QString artistName, int artistId) : RessourceItem(artistName)
{
    m_artistId = artistId;
    this->connector = connector;
    this->m_type = Artist;
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
