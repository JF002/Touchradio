#include "artistitem.h"
#include "ressourceItem.h"

/** Create a new instance of ArtistItem. The instance will be initialized with
 *  values coming from a list of keys-values.
 *  Keys :
 *      - id
 *      - artist */
ArtistItem::ArtistItem(LmsConnector* connector, QMap<QString, QString> tokens) : RessourceItem(connector, "")
{
    this->type = RessourceItem::Artist;

    if(tokens.contains("id"))
        this->id = tokens["id"].toInt();
    if(tokens.contains("artist"))
        this->name = tokens["artist"];
}

void ArtistItem::FillSubItems()
{
    QList<AlbumItem*> albumCollection = this->connector->GetAlbumCollection(this->id);
    for(int i = 0; i < albumCollection.count(); i++)
    {
        this->AddItem((RessourceItem*)albumCollection[i]);
    }
}


