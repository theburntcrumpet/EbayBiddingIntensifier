#include <iostream>
#include <cstring>
#include <thread>
#include <ao/ao.h> 
#include <mpg123.h> 
#ifndef MP3PLAYER_H
#define MP3PLAYER_H

using namespace std;


class MP3Player {
private:
    thread m_playbackThread;
    bool m_bIsPlaying;
    string m_strMP3File;
    int m_nLength;
    mpg123_handle * m_pMpgHandle;
    
private:
    void PlayMP3();
    
public:
    void Play();
    bool LoadFile();
    bool IsPlaying(){return m_bIsPlaying;}
    int GetLength(){return m_nLength;}
    thread * GetThread(){return &m_playbackThread;}
    void SetIsPlaying(bool bIsPlaying){m_bIsPlaying = bIsPlaying;}
    MP3Player(string strMP3File);
    ~MP3Player();

};

#endif /* MP3PLAYER_H */

