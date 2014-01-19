#ifndef LMSSTATUS_H
#define LMSSTATUS_H

#include <QObject>
#include <QString>
#include <QList>
//#include "trackitem.h"

class LmsStatus: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString player_name READ GetPlayerName NOTIFY PlayerNameChanged)
    Q_PROPERTY(double mixer_volume READ GetMixerVolume NOTIFY MixerVolumeChanged)
    Q_PROPERTY(QString currentTrackAlbum READ GetCurrentTrackAlbum NOTIFY CurrentTrackAlbumChanged)
    Q_PROPERTY(QString currentTrackArtist READ GetCurrentTrackArtist NOTIFY CurrentTrackArtistChanged)
    Q_PROPERTY(QString currentTrackTitle READ GetCurrentTrackTitle NOTIFY CurrentTrackTitleChanged)
    Q_PROPERTY(QString currentTrackCoverId READ GetCurrentTrackCoverId NOTIFY CurrentTrackCoverIdChanged)
    Q_PROPERTY(QString currentTrackCoverUrl READ GetCurrentTrackCoverUrl NOTIFY CurrentTrackCoverUrlChanged)
    Q_PROPERTY(double currentTrackDuration READ GetCurrentTrackDuration NOTIFY CurrentTrackDurationChanged)
    Q_PROPERTY(double currentTrackTime READ GetCurrentTrackTime NOTIFY CurrentTrackTimeChanged)
    Q_PROPERTY(QString mode READ GetCurrentMode NOTIFY ModeChanged)
    Q_PROPERTY(QString lmsAddress READ GetLmsAddress NOTIFY LmsAddressChanged)
public:
    LmsStatus();

    void Update(const QString &strStatus);
    QString GetPlayerName();
    double GetMixerVolume();

    QString GetCurrentTrackTitle();
    QString GetCurrentTrackArtist();
    QString GetCurrentTrackAlbum();
    QString GetCurrentTrackCoverId();
    double GetCurrentTrackTime();
    double GetCurrentTrackDuration();
    QString GetCurrentTrackCoverUrl();
    QString GetCurrentMode();
    QString GetLmsAddress();

    void SetLmsAddress(QString address);
Q_SIGNALS:
    void PlayerNameChanged();
    void MixerVolumeChanged();
    void CurrentTrackAlbumChanged();
    void CurrentTrackArtistChanged();
    void CurrentTrackTitleChanged();
    void CurrentTrackCoverIdChanged();
    void CurrentTrackDurationChanged();
    void CurrentTrackTimeChanged();
    void CurrentTrackCoverUrlChanged();
    void LmsAddressChanged();
    void ModeChanged();

protected:
    QList<QString> knowTokens;
    QList<QString> knowTrackTokens;
    void UpdateField(const QString& token, const QString& currentSt);
    void UpdateTrackField(const QString& token, const QString& currentSt);
    
    QString player_name;
    bool player_connected;
    QString player_ip;
    bool power;
    int signalstrength;
    QString mode;
    double currentTrackTime;
    double rate;
    double currentTrackDuration;
    bool can_seek;
    double mixer_volume;
    bool playlist_repeat;
    bool playlist_shuffle;
    bool playlist_mode;
    int seq_no;
    int playlist_cur_index;
    double playlist_timestamp;

    QString currentTrackAlbum;
    QString currentTrackArtist;
    QString currentTrackTitle;
    QString currentTrackCoverId;

    QString lmsAddress;

    void SetPlayerName(const QString& playerName);
    void SetMixerVolume(double volume);
    void SetCurrentTrack(const QString& currentTrackStr);

    void SetCurrentTrackTitle(const QString& title);
    void SetCurrentTrackArtist(const QString& artist);
    void SetCurrentTrackAlbum(const QString& album);
    void SetCurrentTrackCoverId(const QString& coverid);
    void SetCurrentTrackTime(double time);
    void SetCurrentTrackDuration(double duration);
    void SetCurrentMode(const QString& mode);
    
};

#endif // LMSSTATUS_H
