#include "camera.h"
#include "receiver.h"
#include "audioMixer_template.h"

// Test program to convert a2d to wave.
int main(int argc, const char *argv[]) {
    startReceiver();
    startCamera();
    AudioMixer_init();
    while (1) {
    };

    stopReceiver();
    stopCamera();

    return 0;
}