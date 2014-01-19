#ifndef ARTISTITEM_H
#define ARTISTITEM_H

#include "ressourceItem.h"



class ArtistItem : public RessourceItem
{
    Q_OBJECT

public:
    ArtistItem(LmsConnector* connector, QMap<QString, QString> tokens);

    virtual QString GetCoverUrl();
private:
    virtual void FillSubItems();
};


#endif // ARTISTITEM_H
