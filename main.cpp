#include <cstdlib>
#include <iomanip>
#include "MP3Player.h"
#include <unistd.h>
using namespace std;

void PrintUsage(char * strBinaryName){
    cout << "Usage:\n\t\t"<<strBinaryName<<" mp3File.mp3 \"yyyy-mm-dd hh::mm:ss\"" << endl;
}

time_t GetCurrentLocalTime(){
    time_t tUTC;
    tm tmLocal;
    // Get the current UTC Time
    time(&tUTC);
    // Localize that in a tm
    tmLocal = *(localtime(&tUTC));
    
    // Set the GMT offset in the tm to 0. This will fool mktime into giving us the
    // time_t localized
    tmLocal.tm_gmtoff = 0;
    tmLocal.tm_isdst = 0;
    
    return mktime(&tmLocal);
}

int main(int argc, char** argv) {
    
    if(argc != 3){
        PrintUsage(argv[0]);
        return -1;
    }
    
    // We got this far so must have an argument for the mp3 name
    MP3Player mainPlayer(argv[1]);
    if(argc == 2){
        // Wait for the MP3 to play and then bail out.
        mainPlayer.Play();
        while(mainPlayer.IsPlaying()){}
        return 0;
    }
    // Great, a time was specified. Play the song the song the songs length before the time.
    tm tSpecified;
    // Read in the time specified by the user
    stringstream streamSpecifiedTime(argv[2]);
    streamSpecifiedTime >> get_time(&tSpecified,"%Y-%m-%d %H:%M:%S");
    // Do this so that mktime doesn't assume it's got to convert from another timezone when doing mktime
    tSpecified.tm_gmtoff = 0;
    tSpecified.tm_isdst = 0;
    time_t destTime = mktime(&tSpecified);
    destTime = destTime - mainPlayer.GetLength();
    time_t currentTime = GetCurrentLocalTime();
    cout << (destTime - currentTime) << endl;
    while(currentTime < destTime){
        currentTime = GetCurrentLocalTime();
        usleep(1000000);
    }
    
    mainPlayer.Play();
    while(mainPlayer.IsPlaying()){
        usleep(1000000);
    }
    return 0;
}   
