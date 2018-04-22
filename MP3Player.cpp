#include "MP3Player.h"

MP3Player::MP3Player(string strMP3File) {
    mpg123_init();
    ao_initialize();
    m_bIsPlaying = false;
    m_strMP3File = strMP3File;
    // may as well load it on construction
    LoadFile();
}

MP3Player::~MP3Player() {
}

void MP3Player::PlayMP3(){ 
    // if the object doesn't exist, load the file which should create it
    // if it fails then don't continue
    
    cout << "Playing " << m_strMP3File.c_str() << endl;
    int nChannels,nEncoding,nDriver;
    long int nRate;
    size_t done;
    nDriver = ao_default_driver_id();
    int buffer_size = mpg123_outblock(m_pMpgHandle);
    unsigned char * buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
    
    ao_sample_format format;
    
    mpg123_getformat(m_pMpgHandle, &nRate, &nChannels, &nEncoding);
    format.bits = mpg123_encsize(nEncoding) * 8;
    format.rate = nRate;
    format.channels = nChannels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    
    ao_device * dev = ao_open_live(nDriver,&format,NULL);
    while(mpg123_read(m_pMpgHandle,buffer,buffer_size,&done) == MPG123_OK && m_bIsPlaying)
        ao_play(dev,(char*)buffer,done);
    

    
    free(buffer);
    ao_close(dev);
    mpg123_close(m_pMpgHandle);
    mpg123_delete(m_pMpgHandle);
    m_bIsPlaying = false;
}

void MP3Player::Play(){
    // This library doesn't seem to support playing the same file concurrently,
    // so don't play it in this object if it's already playing
    if(m_bIsPlaying)
        return;
    LoadFile();
    m_bIsPlaying = true;
    m_playbackThread = thread(&MP3Player::PlayMP3,this);
    m_playbackThread.detach();
}

bool MP3Player::LoadFile(){
    
    // if the file is already loaded then we want to reload it
    int nChannels,nEncoding;
    long int nRate;
    m_pMpgHandle = mpg123_new(NULL, NULL);
    if(mpg123_open(m_pMpgHandle, m_strMP3File.c_str()))
        return false;
    mpg123_getformat(m_pMpgHandle, &nRate, &nChannels, &nEncoding);
    m_nLength = mpg123_length(m_pMpgHandle)/nRate;
    return true;
}