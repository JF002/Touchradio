#ifndef ARTISTITEM_H
#define ARTISTITEM_H

#include "lmsconnector.h"
#include "RessourceItem.h"

class LMSConnector;

class ArtistItem : public RessourceItem
{
public:
    ArtistItem();
    ArtistItem(LMSConnector* connector, const QString artistName, int artistId);

    int GetArtistId();

public slots:
    QString toString() const;

protected:
    LMSConnector* connector;
    virtual void FillSubItems();

private:
    int m_artistId;
};

#endif // ARTISTITEM_H
