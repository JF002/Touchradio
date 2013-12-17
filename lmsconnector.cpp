#include "lmsconnector.h"
#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QUrl>

#include "artistitem.h"
#include "favoriteitem.h"

LMSConnector::LMSConnector() : QObject(NULL)
{
    socket = new QTcpSocket();
    QObject::connect(this->socket, &QTcpSocket::readyRead, this, &LMSConnector::dataReceived);
    QObject::connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(socketError(QAbstractSocket::SocketError)));



}

LMSConnector::LMSConnector(QObject* parent):   QObject(parent)
{
    socket = new QTcpSocket();
    QObject::connect(this->socket, &QTcpSocket::readyRead, this, &LMSConnector::dataReceived);
    QObject::connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(socketError(QAbstractSocket::SocketError)));


}

QString LMSConnector::ReadPlayerId(int index)
{
    QString id;
    QString answer = this->request(QString("player id %1 ?").arg(index));

    if(answer.startsWith(QString("player id %1").arg(index)))
    {
        id = answer.section(" ",3,3);
    }
    else
    {
        id = QString("");
    }


    return id;
}

void LMSConnector::connect(const QHostAddress & address, quint16 port)
{
    bool connected = false;
    int retries = 60;

    while(!connected && retries > 0)
    {
        socket->connectToHost(address, port);
        connected = socket->waitForConnected(200);
        if(!connected)
        {
            socket->close();
            QThread::msleep(1000);
        }
        qDebug() << "Connection : " << connected;
        retries--;
    }

}

void LMSConnector::BindToPlayer(int index)
{
    this->playerId = ReadPlayerId(index);
}

QString LMSConnector::GetStatus()
{
    QString request = QString("%1 status - 1 tags:alcjK").arg(this->playerId);
    QString answer = this->request(request);
    answer = answer.mid(request.count());
    return answer;
}

QString LMSConnector::GetVersion()
{
    return this->request("version ?");
}

int LMSConnector::GetArtistNumber()
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

QList<FavoriteItem*> LMSConnector::GetFavoriteCollection()
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
            int indexId = row.indexOf("id:") + 3;
            int indexName = row.indexOf(" name:") + 6;
            int indexType = row.indexOf(" type:") +6;
            int indexUrl = row.indexOf(" url:") + 5;
            int indexIsAudio = row.indexOf(" isaudio:") + 9;

            QString idStr = row.mid(indexId, indexName-indexId-6).trimmed();
            QString nameStr = row.mid(indexName, indexType-indexName-6 ).trimmed();
            QString url = row.mid(indexUrl, indexIsAudio - indexUrl - 9).trimmed();

            FavoriteItem* favorite = new FavoriteItem(this, nameStr, idStr);
            favorite->SetUrl(url);
            favoriteCollection.append(favorite);
        }
    }



    return favoriteCollection;
}

QList<ArtistItem*> LMSConnector::GetArtistCollection()
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
            int indexId = row.indexOf("id:") + 3;
            int indexName = row.indexOf("artist:");

            QString idStr = row.mid(indexId, indexName-indexId).trimmed();
            QString nameStr = row.mid(indexName + 7).trimmed();
            ArtistItem* artist = new ArtistItem(this, nameStr, idStr.toInt());
            artistCollection.append(artist);
        }
    }
    return artistCollection;
}

QList<AlbumItem*> LMSConnector::GetAlbumCollection(int artistId)
{
    QList<AlbumItem*> albumCollection;
    bool continueLoop = true;
    int counter = 0;

    while(continueLoop == true)
    {
        int startId = counter*50;

        QString answer = this->request(QString("albums %1 %2 artist_id:%3 tags:lyja").arg(QString::number(startId),QString::number(50), QString::number(artistId)));
        int firstIdIndex = answer.indexOf(" id:");
        answer = answer.mid(firstIdIndex).trimmed();
        if(answer.contains("count:"))
            continueLoop = false;
        for(int j = 0; j <50; j++)
        {
            QString row = answer.section(" id:", j,j,QString::SectionIncludeLeadingSep| QString::SectionSkipEmpty).trimmed();
            int indexId = row.indexOf(" id:") + 4;
            int indexName = row.indexOf(" album:") + 7;
            int indexYear = row.indexOf(" year:") + 6;
            int indexCoverId = row.indexOf(" artwork_track_id:") + 18;
            int indexArtist = row.indexOf(" artist:") + 8;

            QString idStr = row.mid(indexId, indexName-indexId - 7).trimmed();
            QString nameStr = row.mid(indexName, indexYear - indexName - 6).trimmed();
            QString yearStr = row.mid(indexYear, indexCoverId-indexYear-18).trimmed();
            int year = yearStr.toInt();
            QString coverId = row.mid(indexCoverId, indexArtist - indexCoverId - 8).trimmed();
            QString artist = row.mid(indexArtist, row.count() - indexArtist).trimmed();

            AlbumItem* album = new AlbumItem(this, artistId, nameStr, idStr.toInt());
            album->SetYear(year);
            album->SetCoverId(coverId);
            album->SetArtistName(artist);
            albumCollection.append(album);
        }
        counter++;
    }
    return albumCollection;
}

QList<TrackItem*> LMSConnector::GetTrackCollection(int albumId)
{
    QList<TrackItem*> trackCollection;
    bool continueLoop = true;
    int counter = 0;

    while(continueLoop == true)
    {
        int startId = counter*50;

        QString answer = this->request(QString("titles %1 %2 album_id:%3 tags:galdtlyc sort:albumtrack").arg(QString::number(startId),QString::number(50), QString::number(albumId)));
        int firstIdIndex = answer.indexOf(" id:");
        answer = answer.mid(firstIdIndex).trimmed();
        if(answer.contains(" count:"))
            continueLoop = false;
        for(int j = 0; j <50; j++)
        {
            QString row = answer.section(" id:", j,j,QString::SectionIncludeLeadingSep| QString::SectionSkipEmpty).trimmed();
            int indexId = row.indexOf("id:") + 3;
            int indexName = row.indexOf(" title:") + 7;
            int indexGenre = row.indexOf(" genre:") +7;
            int indexArtist = row.indexOf(" artist:") + 8;
            int indexAlbum = row.indexOf(" album:") + 7;
            int indexDuration = row.indexOf(" duration:") +10;
            int indexTrackNum = row.indexOf(" tracknum:") + 10;
            int indexYear = row.indexOf(" year:") + 6;
            int indexCoverid = row.indexOf(" coverid:") + 9;

            QString idStr = row.mid(indexId, indexName-indexId-7).trimmed();
            QString nameStr = row.mid(indexName, indexGenre-indexName-7 ).trimmed();
            QString genreStr = row.mid(indexGenre, indexArtist-indexGenre-8).trimmed();
            QString artistStr = row.mid(indexArtist, indexAlbum-indexArtist-7).trimmed();
            QString albumStr = row.mid(indexAlbum, indexDuration-indexAlbum-10).trimmed();
            QString durationStr = row.mid(indexDuration, indexTrackNum-indexDuration-10).trimmed();
            QString trackNumStr = row.mid(indexTrackNum, indexYear - indexTrackNum-6).trimmed();

            QString coverId;
            int year;
            if(indexCoverid != -1)
            {
                year = row.mid(indexYear, indexCoverid-indexYear-9).trimmed().toInt();
                coverId = row.mid(indexCoverid, row.count()-indexCoverid).trimmed();
            }
            else
            {
                year = row.mid(indexYear, row.count()-indexYear).trimmed().toInt();
                coverId = QString::null;
            }

            TrackItem* track = new TrackItem(this, albumId, trackNumStr.toInt(), nameStr, idStr.toInt());
            track->SetArtistName(artistStr);
            track->SetCoverId(coverId);
            track->SetDuration(durationStr.toDouble());
            track->SetAlbumName(albumStr);
            track->SetYear(year);
            trackCollection.append(track);
        }
        counter++;
    }
    return trackCollection;
}

void LMSConnector::FillTrackInfo(TrackItem* track)
{
    QString answer = this->request(QString("songinfo 0 100 track_id:%1 tags:adlyc").arg(QString::number(track->GetTrackId())));

    int indexArtist = answer.indexOf(" artist:") + 8;
    int indexDuration = answer.indexOf(" duration:") +10;
    int indexAlbum = answer.indexOf(" album:") + 7;
    int indexYear = answer.indexOf(" year:") + 6;
    int indexCoverid = answer.indexOf(" coverid:") + 9;

    QString artist = answer.mid(indexArtist, indexDuration-indexArtist-10).trimmed();
    double duration = answer.mid(indexDuration, indexAlbum-indexDuration-7).trimmed().toDouble();
    QString album = answer.mid(indexAlbum, indexYear-indexAlbum-6).trimmed();

    QString coverId;
    int year;
    if(indexCoverid != -1)
    {
        year = answer.mid(indexYear, indexCoverid-indexYear-6).trimmed().toInt();
        coverId = answer.mid(indexCoverid, indexDuration-indexCoverid-9).trimmed();
    }
    else
    {
        year = answer.mid(indexYear, answer.count()-indexYear).trimmed().toInt();
        coverId = QString::null;
    }

    track->SetArtistName(artist);
    track->SetCoverId(coverId);
    track->SetDuration(duration);
    track->SetAlbumName(album);
    track->SetYear(year);

}


void LMSConnector::Play(int id, int albumId, int tracknum)
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 playlist clear").arg(pid));

    QString request = QString("%1 playlistcontrol cmd:load album_id:%2 play_index:%3").arg(pid, QString::number(albumId), QString::number(tracknum-1));
    answer = this->request(request);

    answer = this->request(QString("%1 play").arg(pid));
}

void LMSConnector::PlayAlbum(int albumId)
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 playlist clear").arg(pid));

    QString request = QString("%1 playlistcontrol cmd:load album_id:%2").arg(pid, QString::number(albumId));
    answer = this->request(request);

    answer = this->request(QString("%1 play").arg(pid));
}

void LMSConnector::PlayFavorite(const QString& id)
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 playlist clear").arg(pid));

    QString request = QString("%1 favorites playlist play item_id:%2").arg(pid, id);
    answer = this->request(request);
}

void LMSConnector::Play()
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 play").arg(pid));
}

void LMSConnector::TogglePause()
{

    QString pid = this->playerId;

    QString answer = this->request(QString("%1 pause").arg(pid));
}

void LMSConnector::Stop()
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 stop").arg(pid));
}

void LMSConnector::Next()
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 playlist index +1").arg(pid));
}

void LMSConnector::Previous()
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 playlist index -1").arg(pid));
}

void LMSConnector::SetVolume(int volume)
{
    QString pid = this->playerId;

    QString answer = this->request(QString("%1 mixer volume %2").arg(pid, QString::number(volume)));
}

QString LMSConnector::request(QString message)
{
    this->write(message);
    return this->read();
}

void LMSConnector::write(QString message)
{
    message.append(10);
    socket->write(message.toLatin1());
}

QString LMSConnector::read()
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

void LMSConnector::dataReceived()
{
}

void LMSConnector::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error : " << socket->errorString();
    socket->close();
}
