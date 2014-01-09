#include "lmsconnector.h"
#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QUrl>
#include <QtDebug>

#include "artistitem.h"
#include "favoriteitem.h"
#include "Exceptions/timeoutexception.h"

LmsConnector::LmsConnector(QObject* parent):   QObject(parent)
{
    socket = new QTcpSocket();
    QObject::connect(this->socket, &QTcpSocket::readyRead, this, &LmsConnector::dataReceived);
    QObject::connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(socketError(QAbstractSocket::SocketError)));

    trackKeys.append("id");
    trackKeys.append("title");
    trackKeys.append("genre");
    trackKeys.append("artist");
    trackKeys.append("album");
    trackKeys.append("duration");
    trackKeys.append("tracknum");
    trackKeys.append("year");
    trackKeys.append("coverid");
    trackKeys.append("album_id");

    favoriteKeys.append("id");
    favoriteKeys.append("name");
    favoriteKeys.append("type");
    favoriteKeys.append("url");
    favoriteKeys.append("isaudio");

    artistKeys.append("id");
    artistKeys.append("artist");

    albumKeys.append("id");
    albumKeys.append("album");
    albumKeys.append("year");
    albumKeys.append("artwork_track_id");
    albumKeys.append("artist");
    albumKeys.append("artist_id");
}

void LmsConnector::moveToThread(QThread *thread)
{
    ((QObject*)this)->moveToThread(thread);
    socket->moveToThread(thread);
}

void LmsConnector::Close()
{
    socket->close();
}


/* Get the ID (MAC address) of the player identified by index
 * @param index Index of the player
 * @return The Identifier of the player */
QString LmsConnector::ReadPlayerId(int index)
{
    /* Request : "player id 0 ?"
     * Answer : "player id 0 9f:83:74:25:3e:5c"
     */

    QString id;
    QString request = "player id %1";
    QString answer = this->request(QString(request + " ?").arg(index));

    if(answer.startsWith(request.arg(index)))
    {
        id = answer.remove(0, request.length()).trimmed();
    }
    else
    {
        id = QString("");
    }

    return id;
}

bool LmsConnector::connect(const QHostAddress & address, quint16 port)
{
    bool connected = false;
    int retries = 60;
    this->address = address;
    this->port = port;


    while(!connected && retries > 0)
    {
        socket->connectToHost(address, port);
        connected = socket->waitForConnected(1000);
        if(!connected)
        {
            qWarning() << "Error : " << socket->error();
            QThread::msleep(1000);
        }
        retries--;
    }
    return connected;

}

QString LmsConnector::GetLmsAddress()
{
    return this->address.toString() + ":" + QString::number(this->port);
}

void LmsConnector::BindToPlayer(int index)
{
    this->playerId = ReadPlayerId(index);
}

/* Get a string from the server describing its status.
 * This string is intended to be handled by a LmsStatus object */
QString LmsConnector::GetStatus()
{
    /* Request : "xx:xx:xx:xx:xx:xx status - 1 tags:alcjK"
     * Response :
     *      player_name:SoftSqueeze player_connected:1 player_ip:192.168.0.2:62698
     *      power:1 signalstrength:0 mode:play remote:1 current_title: - Lazy Bones
     *      time:2209.14036511421 rate:1 mixer volume:73 playlist repeat:0 playlist
     *      shuffle:0 playlist mode:off seq_no:0 playlist_cur_index:0 playlist_timestamp:1387747708.53505
     *      playlist_tracks:1 remoteMeta:HASH(0x47838c0) playlist index:0 id:-73516576 title:Lazy Bones
     *      coverid:-73516576 coverart:0 */
    QString request = QString("%1 status - 1 tags:alcjK").arg(this->playerId);
    QString answer = this->request(request);
    answer = answer.mid(request.count());
    return answer;
}

/* Returns the version of the LMS server */
QString LmsConnector::GetVersion()
{
    /* Request : "version ?"
     * Answer : "version 7.7.3" */
    return this->request("version ?");
}

int LmsConnector::GetArtistNumber()
{
    QString answer = this->request("info total artists ?");
    answer = answer.section("info total artists ",1,1);
    bool ok;
    int number = answer.toInt(&ok);
    if(ok)
        return number;
    else
        return 0;
}

QList<FavoriteItem*> LmsConnector::GetFavoriteCollection()
{
    bool finished = false;
    QList<FavoriteItem*> favoriteCollection;

    int currentIndex = 0;
    int currentCount;
    while(!finished)
    {
        QString answer = this->request(QString("favorites items %1 %2 want_url:1").arg(QString::number(currentIndex),QString::number(50)));
        int currentCountIndex = answer.indexOf(" count:") + 7;
        currentCount = answer.mid(currentCountIndex, answer.count()-currentCountIndex).trimmed().toInt();
        if(currentCount < 50)
            finished = true;

        for(int i = 0; i < currentCount; i++)
        {
            int firstIdIndex = answer.indexOf("id:");
            answer = answer.mid(firstIdIndex).trimmed();

            QString row = answer.section("id:", i,i,QString::SectionIncludeLeadingSep| QString::SectionSkipEmpty).trimmed();
            QMap<QString, QString> results = this->ParseAnswer(row, favoriteKeys);
            FavoriteItem* favorite = new FavoriteItem(this, results);

            favoriteCollection.append(favorite);
        }
    }

    return favoriteCollection;
}

QList<ArtistItem*> LmsConnector::GetArtistCollection()
{
    QList<ArtistItem*> artistCollection;
    int artistCount = GetArtistNumber();
    int loopCount = (artistCount / 50) + 1;

    for(int i = 0; i < loopCount; i++)
    {
        int startId = i*50;

        QString answer = this->request(QString("artists %1 %2").arg(QString::number(startId),QString::number(50)));
        int firstIdIndex = answer.indexOf("id:");
        answer = answer.mid(firstIdIndex);
        for(int j = 0; j <50; j++)
        {
            QString row = answer.section("id:", j,j,QString::SectionIncludeLeadingSep| QString::SectionSkipEmpty).trimmed();
            QMap<QString, QString> results = this->ParseAnswer(row, artistKeys);
            ArtistItem* artist = new ArtistItem(this, results);
            artistCollection.append(artist);
        }
    }
    return artistCollection;
}

QList<AlbumItem*> LmsConnector::GetAlbumCollection(int artistId)
{
    QList<AlbumItem*> albumCollection;
    bool continueLoop = true;
    int counter = 0;

    while(continueLoop == true)
    {
        int startId = counter*50;

        QString answer = this->request(QString("albums %1 %2 artist_id:%3 tags:lyjaS").arg(QString::number(startId),QString::number(50), QString::number(artistId)));
        int firstIdIndex = answer.indexOf(" id:");
        answer = answer.mid(firstIdIndex).trimmed();
        if(answer.contains("count:"))
            continueLoop = false;
        for(int j = 0; j <50; j++)
        {
            QString row = answer.section(" id:", j,j,QString::SectionIncludeLeadingSep| QString::SectionSkipEmpty).trimmed();
            QMap<QString, QString> results = this->ParseAnswer(row, albumKeys);
            AlbumItem* album = new AlbumItem(this, results);
            albumCollection.append(album);
        }
        counter++;
    }
    return albumCollection;
}

QList<TrackItem*> LmsConnector::GetTrackCollection(int albumId)
{
    QList<TrackItem*> trackCollection;
    bool continueLoop = true;
    int counter = 0;

    while(continueLoop == true)
    {
        int startId = counter*50;

        QString answer = this->request(QString("titles %1 %2 album_id:%3 tags:galdtlyce sort:albumtrack").arg(QString::number(startId),QString::number(50), QString::number(albumId)));
        int firstIdIndex = answer.indexOf(" id:");
        answer = answer.mid(firstIdIndex).trimmed();
        if(answer.contains(" count:"))
            continueLoop = false;
        for(int j = 0; j <50; j++)
        {
            QString row = answer.section(" id:", j,j,QString::SectionIncludeLeadingSep| QString::SectionSkipEmpty).trimmed();
            QMap<QString, QString> results = this->ParseAnswer(row, trackKeys);
            TrackItem* track = new TrackItem(this, results);
            trackCollection.append(track);
        }
        counter++;
    }
    return trackCollection;
}

QMap<QString, QString> LmsConnector::ParseAnswer(QString response, QList<QString> knownKeys)
{
    QString currentKey;
    QMap<QString, QString> values;
    if(!response.startsWith(" "))
        response.insert(0," ");
    foreach(currentKey, knownKeys)
    {
        int keyIndex = response.indexOf(" " + currentKey + ":", 0, Qt::CaseSensitive);
        if(keyIndex == -1)
            continue;

        keyIndex+=currentKey.count()+2;
        int nextIndex = response.indexOf(QRegExp("(\\s[^\\s]+[:]){1}", Qt::CaseSensitive, QRegExp::RegExp2), keyIndex);
        QString token = response.mid(keyIndex, nextIndex- keyIndex);
        values[currentKey] = token;
    }
    return values;
}


void LmsConnector::Play(int id, int albumId, int tracknum)
{
    QString answer = this->request(QString("%1 playlist clear").arg(this->playerId));
    QString request = QString("%1 playlistcontrol cmd:load album_id:%2 play_index:%3").arg(this->playerId, QString::number(albumId), QString::number(tracknum-1));
    answer = this->request(request);
    answer = this->request(QString("%1 play").arg(this->playerId));
}

void LmsConnector::PlayAlbum(int albumId)
{
    QString answer = this->request(QString("%1 playlist clear").arg(this->playerId));
    QString request = QString("%1 playlistcontrol cmd:load album_id:%2").arg(this->playerId, QString::number(albumId));
    answer = this->request(request);
    answer = this->request(QString("%1 play").arg(this->playerId));
}

void LmsConnector::PlayFavorite(const QString& id)
{
    QString answer = this->request(QString("%1 playlist clear").arg(this->playerId));
    QString request = QString("%1 favorites playlist play item_id:%2").arg(this->playerId, id);
    answer = this->request(request);
}

void LmsConnector::Play()
{
    QString answer = this->request(QString("%1 play").arg(this->playerId));
}

void LmsConnector::TogglePause()
{
    QString answer = this->request(QString("%1 pause").arg(this->playerId));
}

void LmsConnector::Stop()
{
    QString answer = this->request(QString("%1 stop").arg(this->playerId));
}

void LmsConnector::Next()
{
    QString answer = this->request(QString("%1 playlist index +1").arg(this->playerId));
}

void LmsConnector::Previous()
{
    QString answer = this->request(QString("%1 playlist index -1").arg(this->playerId));
}

void LmsConnector::SetVolume(int volume)
{
    QString answer = this->request(QString("%1 mixer volume %2").arg(this->playerId, QString::number(volume)));
}

QString LmsConnector::GetUnknownCoverUrl()
{
    return "http://" + address.toString() + ":9000/music/0/cover_150x150_o";
}

QString LmsConnector::GetCoverUrl(QString& coverId)
{
    return "http://" + address.toString() + ":9000/music/" + coverId + "/cover.jpg";
}

QString LmsConnector::request(QString message)
{
    this->write(message);
    return this->read();
}

QString LmsConnector::GetRadioCoverUrl()
{
    return "http://" + address.toString() + ":9000/html/images/radio.png";
}

void LmsConnector::write(QString message)
{
    message.append(10);
    socket->write(message.toLatin1());
}

QString LmsConnector::read()
{
    char buffer[10240];
    bool fullLine = false;
    QByteArray byteArray;
    while(!fullLine)
    {
        bool ready = socket->waitForReadyRead();
        if(ready)
        {
            qint64 ret = socket->readLine(buffer, 10240);
            if(ret !=-1)
            {
                byteArray.append(buffer, ret);
                if(buffer[ret-1] == '\n')
                    fullLine = true;
            }
            else
            {
                qDebug() << "Read error";
                return NULL;
            }
        }
        else
        {
            qDebug() << "Read: No data";
        }
    }
    QString value= QUrl::fromPercentEncoding(byteArray).trimmed();
    return value;
}

void LmsConnector::dataReceived()
{
}

void LmsConnector::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error : " << socket->errorString();
    socket->close();
}
