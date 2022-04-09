#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <sndfile.hh>
#include <thread>

#include "RtAudio.h"

typedef struct {
    SndfileHandle *playback_file;
    SndfileHandle *record_file;
    bool *run_playback;
    bool *run_record;
} callback_t;

class Audio {

    RtAudio rt;
    unsigned int bufferFrames;
    unsigned int sampleRate;
    callback_t rtCallbackInfo;

    bool runPlayback;
    RtAudio::StreamParameters playbackParams;
    SndfileHandle playbackFile;

    bool runRecord;
    std::thread recordThread;
    RtAudio::StreamParameters recordParams;
    SndfileHandle recordFile;

  public:
    Audio();
    ~Audio();

    void record(const char *filename);

    void startPlayback(const char *filename);
    void stopPlayback();
};

#endif //_AUDIO_H_