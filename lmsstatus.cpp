#include "lmsstatus.h"
#include <QDebug>

LmsStatus::LmsStatus()
{
    this->knowTokens.append("player_name");
    this->knowTokens.append("player_connected");
    this->knowTokens.append("player_ip");
    this->knowTokens.append("power");
    this->knowTokens.append("signalstrength");
    this->knowTokens.append("mode");
    this->knowTokens.append("time");
    this->knowTokens.append("rate");
    this->knowTokens.append("duration");
    this->knowTokens.append("can_seek");
    this->knowTokens.append("mixer volume");
    this->knowTokens.append("playlist repeat");
    this->knowTokens.append("playlist shuffle");
    this->knowTokens.append("playlist mode");
    this->knowTokens.append("seq_no");
    this->knowTokens.append("playlist_cur_index");
    this->knowTokens.append("playlist_timestamp");
    this->knowTokens.append("playlist_tracks");
    this->knowTokens.append("playlist index");
    this->knowTokens.append("index");

    this->knowTrackTokens.append("index");
    this->knowTrackTokens.append("title");
    this->knowTrackTokens.append("artist");
    this->knowTrackTokens.append("album");
    this->knowTrackTokens.append("coverid");
    this->knowTrackTokens.append("coverart");
    this->lmsAddress = "0.0.0.0";
}

void LmsStatus::SetLmsAddress(QString address)
{
    if(this->lmsAddress != address)
    {
        this->lmsAddress = address;
        emit LmsAddressChanged();
    }
}

QString LmsStatus::GetLmsAddress(){
    return this->lmsAddress;
}

void LmsStatus::Update(const QString& strStatus)
{
    QString token;
    foreach(token, knowTokens)
    {
        int indexCurrent = strStatus.indexOf(token);
        bool found = (indexCurrent != -1);


        int indexNext;
        if(token != "index")
        {
            indexCurrent+=token.count() + 1;
            indexNext = strStatus.indexOf(" ", indexCurrent);
            if(indexNext == -1)
                indexNext = strStatus.count() -1;
        }
        else
        {
            // assume only 1 track is present in the status string
            indexNext = strStatus.count();
        }

        if(found)
        {

            QString currentStr = strStatus.mid(indexCurrent, indexNext - indexCurrent);
            UpdateField(token, currentStr);
        }
    }


}

void LmsStatus::UpdateField(const QString& token, const QString& currentSt)
{
    if(token == "player_name")
        SetPlayerName(currentSt);
    else if (token == "player_connected")
        player_connected = (currentSt == "1");
    else if (token == "player_ip")
        player_ip = currentSt;
    else if (token == "power")
        power = (currentSt == "1");
    else if (token == "signalstrength")
        signalstrength = currentSt.toInt();
    else if (token ==  "mode")
        SetCurrentMode(currentSt);
    else if (token == "time")
        SetCurrentTrackTime(currentSt.toDouble());
    else if (token == "rate")
        rate = currentSt.toDouble();
    else if (token == "duration")
        SetCurrentTrackDuration(currentSt.toDouble());
    else if (token == "can_seek")
        can_seek = (currentSt == "1");
    else if (token == "mixer volume")
        SetMixerVolume(currentSt.toDouble());
    else if (token == "playlist repeat")
        playlist_repeat = (currentSt == "1");
    else if (token == "playlist shuffle")
        playlist_shuffle = (currentSt == "1");
    else if (token == "playlist mode")
        playlist_mode = (currentSt == "on");
    else if (token == "seq_no")
        seq_no = currentSt.toInt();
    else if (token == "playlist_cur_index")
        playlist_cur_index = currentSt.toInt();
    else if (token == "playlist_timestamp")
        playlist_timestamp = currentSt.toDouble();
    else if (token == "index")
        SetCurrentTrack(currentSt);
}

void LmsStatus::UpdateTrackField(const QString& token, const QString& currentSt)
{
    if(token == "title")
        SetCurrentTrackTitle(currentSt);
    else if (token == "artist")
        SetCurrentTrackArtist(currentSt);
    else if (token == "album")
        SetCurrentTrackAlbum(currentSt);
    else if (token == "coverid")
        SetCurrentTrackCoverId(currentSt);
}

QString LmsStatus::GetPlayerName()
{
    return player_name;
}

double LmsStatus::GetMixerVolume()
{
    return mixer_volume;
}

void LmsStatus::SetPlayerName(const QString& playerName)
{
    if(playerName != player_name)
    {
        player_name = playerName;
        emit PlayerNameChanged();
    }
}

QString LmsStatus::GetCurrentMode()
{
    return this->mode;
}

void LmsStatus::SetCurrentMode(const QString& mode)
{
    if(mode != this->mode)
    {
        this->mode = mode;
        emit ModeChanged();
    }
}

void LmsStatus::SetMixerVolume(double volume)
{
    if(volume != mixer_volume)
    {
        mixer_volume = volume;

        emit MixerVolumeChanged();
    }
}

void LmsStatus::SetCurrentTrack(const QString& currentTrackStr)
{
    QString token;
    foreach(token, knowTrackTokens)
    {
        int indexCurrent = currentTrackStr.indexOf(token);
        bool found = (indexCurrent != -1);
        indexCurrent+=token.count() + 1;

        int indexNext = currentTrackStr.indexOf(":", indexCurrent);

        bool nextItemPresent = true;
        if(indexNext == -1)
        {
            indexNext = currentTrackStr.count();
            nextItemPresent = false;
        }

        if(found)
        {

            QString currentStr = currentTrackStr.mid(indexCurrent, indexNext - indexCurrent);

            if(nextItemPresent)
            {
                int lastSpace = currentStr.lastIndexOf(" ");
                currentStr = currentStr.left(currentStr.count() - (currentStr.count() -lastSpace));
            }
            UpdateTrackField(token, currentStr);
        }
    }
}

QString LmsStatus::GetCurrentTrackTitle()
{
    return currentTrackTitle;
}

QString LmsStatus::GetCurrentTrackArtist()
{
    return currentTrackArtist;
}

QString LmsStatus::GetCurrentTrackAlbum()
{
    return currentTrackAlbum;
}

QString LmsStatus::GetCurrentTrackCoverId()
{
    return currentTrackCoverId;
}

QString LmsStatus::GetCurrentTrackCoverUrl()
{
    // TODO Get the URL from the server, do not use these constants
    if(currentTrackCoverId == QString::null)
        return "http://192.168.0.7:9000/music/0/cover_150x150_o";
    else
        return "http://192.168.0.7:9000/music/" + currentTrackCoverId + "/cover.jpg";
}

void LmsStatus::SetCurrentTrackTitle(const QString& title)
{
    if(title!= currentTrackTitle)
    {
        currentTrackTitle =title;
        emit CurrentTrackTitleChanged();
    }
}

void LmsStatus::SetCurrentTrackArtist(const QString& artist)
{
    if(artist!= currentTrackArtist)
    {
        currentTrackArtist =artist;
        emit CurrentTrackArtistChanged();
    }
}

void LmsStatus::SetCurrentTrackAlbum(const QString& album)
{
    if(album!= currentTrackAlbum)
    {
        currentTrackAlbum =album;
        emit CurrentTrackAlbumChanged();
    }
}

void LmsStatus::SetCurrentTrackCoverId(const QString& coverid)
{
    if(coverid!= currentTrackCoverId)
    {
        currentTrackCoverId =coverid;
        emit CurrentTrackCoverIdChanged();
        emit CurrentTrackCoverUrlChanged();
    }
}

double LmsStatus::GetCurrentTrackTime()
{
    return this->currentTrackTime;
}

double LmsStatus::GetCurrentTrackDuration()
{
    return this->currentTrackDuration;
}

void LmsStatus::SetCurrentTrackTime(double time)
{
    if(time!= this->currentTrackTime)
    {
        this->currentTrackTime =time;
        emit CurrentTrackTimeChanged();
    }
}

void LmsStatus::SetCurrentTrackDuration(double duration)
{
    if(duration != this->currentTrackDuration)
    {
        this->currentTrackDuration = duration;
        emit CurrentTrackDurationChanged();
    }
}
