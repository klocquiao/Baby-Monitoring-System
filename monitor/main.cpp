#include <iostream>
#include <string>

#include "audio.h"
#include "camera.h"
#include "receiver.h"
#include "wave_loader.hpp"

#define BUFFER_LEN 1024

int main(int argc, const char *argv[]) {
    startCamera();
    Audio audio;
    startReceiver();

    while (1) {
    };

    stopReceiver();
    // stopCamera();

    return 0;
}
