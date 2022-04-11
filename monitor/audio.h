#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <portaudio.h>
#include <sndfile.hh>
#include <thread>

class Audio {

    PaStream *playbackStream;
    PaStreamParameters playbackParams;
    SndfileHandle playbackFile;
    bool playbackRunning;

    PaStream *recordStream;
    PaStreamParameters recordParams;
    SndfileHandle recordFile;
    bool runRecord;
    std::thread recordThread;

    bool audioDetected;
    std::thread a2dThread;

  public:
    Audio();
    ~Audio();

    void record(const char *filename);

    bool isAudioDetected();

    void startPlayback(const char *filename);
    void stopPlayback();
};

#endif //_AUDIO_H_