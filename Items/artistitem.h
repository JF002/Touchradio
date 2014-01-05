#ifndef ARTISTITEM_H
#define ARTISTITEM_H

#include "lmsconnector.h"
#include "ressourceItem.h"

class LmsConnector;

class ArtistItem : public RessourceItem
{
public:
    ArtistItem();
    ArtistItem(LmsConnector* connector, const QString artistName, int artistId);
    ArtistItem(LmsConnector* connector, QMap<QString, QString> tokens);

    int GetArtistId();

public slots:
    QString toString() const;

protected:
    LmsConnector* connector;
    virtual void FillSubItems();

private:
    int m_artistId;
};

#endif // ARTISTITEM_H
