#include <iostream>
#include <string>

#include "RtAudio.h"
#include "camera.h"
#include "receiver.h"
#include "wave_loader.hpp"

#define BUFFER_LEN 1024

int main(int argc, const char *argv[]) {
    // startReceiver();
    // startCamera();

    // while (1) {
    // };

    // stopReceiver();
    // stopCamera();

    //     if (status)
    //         std::cout << "Stream overflow detected!" << std::endl;
    //     // Do something with the data in the "inputBuffer" buffer.

    //     for (unsigned int i = 0; i < nBufferFrames; i++) {
    //         *out++ = *in++;
    //     }

    //     return 0;
    // }

    // static SndfileHandle infile;

    // int playback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status) {
    //     return 0;
    // }

    // RtAudio rt;
    // int deviceCount = rt.getDeviceCount();
    // if (deviceCount < 1) {
    //     std::cout << "\nNo audio devices found!\n";
    //     exit(1);
    // }

    // RtAudio::DeviceInfo info;
    // int inputDeviceId = rt.getDefaultInputDevice();
    // info = rt.getDeviceInfo(inputDeviceId);
    // std::cout << "device[" << inputDeviceId << "]: name = " << info.name << ", maximum input channels = " << info.inputChannels << ", maximum output channels = " << info.outputChannels << "\n";
    // // for (int i = 0; i < deviceCount; i++) {
    // //     info = rt.getDeviceInfo(i);
    // //     if (info.probed == true) {
    // //         // Print, for example, the maximum number of output channels for each device
    // //         std::cout << "device[" << i << "]: name = " << info.name << ", maximum input channels = " << info.inputChannels << ", maximum output channels = " << info.outputChannels << "\n";
    // //         if (info.name == "hw:USB PnP Sound Device,0") {
    // //             inputDeviceId = i;
    // //         }
    // //     }
    // // }

    // if (inputDeviceId == -1) {
    //     std::cout << "\ndeviceId == -1\n";
    //     exit(1);
    // }

    // // Constants
    // // unsigned int sampleRate = 22050;
    // unsigned int bufferFrames = 256; // 256 sample frames

    // RtAudio::StreamParameters inputParams;
    // inputParams.deviceId = inputDeviceId;
    // inputParams.nChannels = 1;
    // inputParams.firstChannel = 0;

    // RtAudio::StreamParameters outputParams;
    // unsigned int outputDeviceId = rt.getDefaultOutputDevice();
    // info = rt.getDeviceInfo(outputDeviceId);
    // std::cout << "device[" << outputDeviceId << "]: name = " << info.name << ", maximum input channels = " << info.inputChannels << ", maximum output channels = " << info.outputChannels << "\n";
    // outputParams.deviceId = outputDeviceId;
    // outputParams.nChannels = 1;
    // outputParams.firstChannel = 0;

    // // wavedata_t wavefile;
    // // std::string filename = "./BabyElephantWalk60.wav";
    // // readWaveFileIntoMemory(filename, &wavefile);

    // SF_INFO sfinfo;
    // const char *infilename = "BabyElephantWalk60.wav";
    // memset(&sfinfo, 0, sizeof(sfinfo));

    // infile = SndfileHandle(infilename);

    // printf("Opened file '%s'\n", infilename);
    // printf("    Sample rate : %d\n", infile.samplerate());
    // printf("    Channels    : %d\n", infile.channels());

    // // Start the stream
    // try {
    //     rt.openStream(&outputParams, NULL, RTAUDIO_SINT16,
    //                   sfinfo.samplerate, &bufferFrames, NULL);
    //     rt.startStream();
    // } catch (RtAudioError &e) {
    //     e.printMessage();
    //     exit(0);
    // }

    // char input;
    // std::cout << "\nPlaying ... press <enter> to quit.\n";
    // std::cin.get(input);

    // // Stop the stream
    // try {
    //     rt.stopStream();
    // } catch (RtAudioError &e) {
    //     e.printMessage();
    // }
    // if (rt.isStreamOpen())
    //     rt.closeStream();
    // return 0;

    // const int rate = 44100;
    // const int duration = 5;
    // const char *filename = "sample.wav";
    // char command[100];
    // printf("Recording...\n");
    // sprintf(command, "arecord --rate=%d --device=\"hw:1,0\" --format=S16_LE %s --duration=%d", rate, filename, duration);
    // system(command);

    // printf("Playback...\n");

    // sprintf(command, "aplay %s", filename);
    // system(command);

    return 0;
}
