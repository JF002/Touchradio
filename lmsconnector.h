#ifndef LMSCONNECTOR_H
#define LMSCONNECTOR_H

#include <QTcpSocket>
#include <QHostAddress>

/*
#include "artistitem.h"
#include "albumitem.h"
#include "trackitem.h"
#include "favoriteitem.h"*/

#include "lmsstatus.h"


class ArtistItem;
class AlbumItem;
class TrackItem;
class FavoriteItem;
class LmsStatusThread;


class LmsConnector : public QObject
{
    Q_OBJECT
public:
    LmsConnector(QObject* parent = NULL);

    bool connect(const QHostAddress & address, quint16 port);
    void Close();

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

    virtual void moveToThread(QThread *thread);

    QString GetCoverUrl(int coverId);
    QString GetRadioCoverUrl();

    QString GetLmsAddress();
    virtual QString GetCoverUrl(QString coverId);

protected:
    void write(QString message);
    QString read();
    QString request(QString message);
    QString ReadPlayerId(int index);

    QMap<QString, QString> ParseAnswer(QString response, QList<QString> knownKeys);




private slots:
    void dataReceived();
    void socketError(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket* socket;
    QString playerId;
    QHostAddress address;
    quint16 port;

    QList<QString> trackKeys;
    QList<QString> favoriteKeys;
    QList<QString> artistKeys;
    QList<QString> albumKeys;
};

#endif // LMSCONNECTOR_H
