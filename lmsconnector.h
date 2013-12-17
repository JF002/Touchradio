#ifndef LMSCONNECTOR_H
#define LMSCONNECTOR_H

#include <QTcpSocket>
#include "artistitem.h"
#include "albumitem.h"
#include "trackitem.h"
#include "lmsstatus.h"

class ArtistItem;
class AlbumItem;
class TrackItem;
class FavoriteItem;
class LMSStatusThread;


class LMSConnector : public QObject
{
    Q_OBJECT
public:
    LMSConnector();
    LMSConnector(QObject* parent);

    void connect(const QHostAddress & address, quint16 port);

    QString GetVersion();
    int GetArtistNumber();
    QList<ArtistItem*> GetArtistCollection();

    QList<AlbumItem*> GetAlbumCollection(int artistId);
    QList<TrackItem*> GetTrackCollection(int albumId);

    QList<FavoriteItem*> GetFavoriteCollection();

    void Play(int id, int albumId, int tracknum);
    void PlayFavorite(const QString &id);
    void PlayAlbum(int albumId);
    void BindToPlayer(int index);
    QString GetStatus();

    void Play();
    void TogglePause();
    void Stop();
    void Next();
    void Previous();

    void SetVolume(int volume);

    void FillTrackInfo(TrackItem* track);

protected:
    void write(QString message);
    QString read();
    QString request(QString message);
    QString ReadPlayerId(int index);




private slots:
    void dataReceived();
    void socketError(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket* socket;
    QString playerId;
};

#endif // LMSCONNECTOR_H
