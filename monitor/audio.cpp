#include <iostream>

#include "audio.h"

#define FRAMES_PER_BUFFER 1024
#define SAMPLE_RATE 44100

#define AUDIO_DEVICE_NAME "USB Device 0x46d:0x825: Audio (hw:1,0)"
#define OUT_FILENAME "out.wav"

int recordCallback(void *input, void *output, unsigned long frameCount,
                   const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    int16_t *in = (int16_t *)input;
    SndfileHandle *record_file = reinterpret_cast<SndfileHandle *>(userData);

    record_file->writef(in, frameCount);

    return 0;
}

int playbackCallback(void *input, void *output, unsigned long frameCount,
                     const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    int16_t *out = (int16_t *)output;
    SndfileHandle *playback_file = reinterpret_cast<SndfileHandle *>(userData);

    sf_count_t readFrames = playback_file->readf(out, frameCount);
    if (readFrames == 0) {
        playback_file->seek(0, SF_SEEK_SET);
    }

    return 0;
}

Audio::Audio() {
    playbackRunning = false;
    runRecord = false;

    // Initialize PortAudio
    PaError err;
    err = Pa_Initialize();
    if (err != paNoError) {
        std::cout << "ERROR: Failed to initialize PortAudio\n";
        exit(EXIT_FAILURE);
    }

    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        std::cout << "ERROR: Pa_CountDevices returned " << numDevices << '\n';
        exit(EXIT_FAILURE);
    }

    const PaDeviceInfo *deviceInfo;
    int inputDeviceId = -1;
    for (int i = 0; i < numDevices; i++) {
        deviceInfo = Pa_GetDeviceInfo(i);
        if (std::string(deviceInfo->name) == AUDIO_DEVICE_NAME) {
            inputDeviceId = i;
        }
    }
    if (inputDeviceId == -1) {
        std::cout << "ERROR: inputDeviceId == -1\n";
        exit(EXIT_FAILURE);
    }

    // Init recording stream
    const PaDeviceInfo *inputDeviceInfo = Pa_GetDeviceInfo(inputDeviceId);
    recordParams.device = inputDeviceId;
    recordParams.hostApiSpecificStreamInfo = NULL;
    recordParams.channelCount = inputDeviceInfo->maxInputChannels;
    recordParams.sampleFormat = paInt16;
    recordParams.suggestedLatency = inputDeviceInfo->defaultLowInputLatency;

    recordFile = SndfileHandle(OUT_FILENAME, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, inputDeviceInfo->maxInputChannels, inputDeviceInfo->defaultSampleRate);

    Pa_OpenStream(&recordStream, &recordParams, NULL, inputDeviceInfo->defaultSampleRate, FRAMES_PER_BUFFER, paNoFlag, (PaStreamCallback *)&recordCallback, (void *)&recordFile);

    // Init playback stream
    int outputDeviceId = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo *outputDeviceInfo = Pa_GetDeviceInfo(outputDeviceId);
    playbackParams.device = outputDeviceId;
    playbackParams.hostApiSpecificStreamInfo = NULL;
    playbackParams.channelCount = 2;
    playbackParams.sampleFormat = paInt16;
    playbackParams.suggestedLatency = outputDeviceInfo->defaultLowOutputLatency;

    Pa_OpenStream(&playbackStream, NULL, &playbackParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag, (PaStreamCallback *)&playbackCallback, (void *)&playbackFile);
}

Audio::~Audio() {
    playbackRunning = false;
    runRecord = false;

    // Stop the stream
    Pa_CloseStream(&playbackStream);
    Pa_CloseStream(&recordStream);

    Pa_Terminate();
}

void Audio::startPlayback(const char *filename) {
    if (playbackRunning) {
        stopPlayback();
    }

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

    playbackRunning = true;
    Pa_StartStream(playbackStream);
}

void Audio::stopPlayback() {
    playbackRunning = false;
    Pa_StopStream(playbackStream);
}