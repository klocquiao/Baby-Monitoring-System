#include "audio.h"

#define BUFFER_LEN 1024
#define SAMPLE_RATE 44100
#define AUDIO_DEVICE_NAME "hw:USB Device 0x46d:0x825,0"

int rtCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
               double streamTime, RtAudioStreamStatus status, void *userData) {
    int16_t *in = (int16_t *)inputBuffer;   // mic
    int16_t *out = (int16_t *)outputBuffer; // speaker
    callback_t *rtCallbackInfo = reinterpret_cast<callback_t *>(userData);

    // Playback
    SndfileHandle *playback_file = rtCallbackInfo->playback_file;
    bool *run_playback = rtCallbackInfo->run_playback;
    if (*run_playback) {
        sf_count_t readFrames = playback_file->readf(out, nBufferFrames);
        if (readFrames == 0) {
            playback_file->seek(0, SF_SEEK_SET);
        }
    }

    // Recording
    SndfileHandle *record_file = rtCallbackInfo->record_file;
    bool *run_record = rtCallbackInfo->run_record;
    if (*run_record) {
        record_file->writef(in, nBufferFrames);
    }

    return 0;
}

Audio::Audio() {
    bufferFrames = BUFFER_LEN;
    sampleRate = SAMPLE_RATE;

    runPlayback = false;
    runRecord = false;

    // Configure RtAudio
    int deviceCount = rt.getDeviceCount();
    if (deviceCount < 1) {
        std::cout << "No audio devices found!\n";
        exit(1);
    }

    RtAudio::DeviceInfo info;
    int inputDeviceId = -1;
    for (int i = 0; i < deviceCount; i++) {
        info = rt.getDeviceInfo(i);
        if (info.probed && info.name == AUDIO_DEVICE_NAME) {
            inputDeviceId = i;
        }
    }

    if (inputDeviceId == -1) {
        std::cout << "Could not find find the correct audio device!\n";
        exit(1);
    }

    info = rt.getDeviceInfo(inputDeviceId);
    recordParams.deviceId = inputDeviceId;
    recordParams.nChannels = info.inputChannels;
    recordParams.firstChannel = 0;

    recordFile = SndfileHandle("out.wav", SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, info.inputChannels, sampleRate);

    unsigned int outputDeviceId = rt.getDefaultOutputDevice();
    playbackParams.deviceId = outputDeviceId;
    playbackParams.nChannels = 2;
    playbackParams.firstChannel = 0;

    rtCallbackInfo.playback_file = &playbackFile;
    rtCallbackInfo.record_file = &recordFile;
    rtCallbackInfo.run_playback = &runPlayback;
    rtCallbackInfo.run_record = &runRecord;

    try {
        rt.openStream(&playbackParams, &recordParams, RTAUDIO_SINT16,
                      sampleRate, &bufferFrames, &rtCallback, (void *)&rtCallbackInfo);
        rt.startStream();
    } catch (RtAudioError &e) {
        e.printMessage();
        exit(1);
    }
}

Audio::~Audio() {
    runPlayback = false;
    runRecord = false;

    // Stop the stream
    try {
        rt.stopStream();
    } catch (RtAudioError &e) {
        e.printMessage();
    }
    if (rt.isStreamOpen())
        rt.closeStream();
}

void Audio::startPlayback(const char *filename) {
    playbackFile = SndfileHandle(filename);
    if (playbackFile.error()) {
        std::cout << "Could not open audio file with specified filename: " << filename << '\n';
        return;
    }

    // Debug message
    std::cout << "Reading file: " << filename << std::endl;
    std::cout << "File format: " << playbackFile.format() << std::endl;
    std::cout << "PCM 16 BIT: " << (SF_FORMAT_WAV | SF_FORMAT_PCM_16) << std::endl;
    std::cout << "Samples in file: " << playbackFile.frames() << std::endl;
    std::cout << "Samplerate " << playbackFile.samplerate() << std::endl;
    std::cout << "Channels: " << playbackFile.channels() << std::endl;

    runPlayback = true;
}

void Audio::stopPlayback() {
    runPlayback = false;
}