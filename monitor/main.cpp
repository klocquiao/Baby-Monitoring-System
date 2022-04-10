#include <iostream>
#include <string>

#include "audio.h"
#include "camera.h"
#include "receiver.h"

int main(int argc, const char *argv[]) {
    startCamera();
    Audio audio;
    startReceiver(&audio);

    while (1) {
    };

    stopReceiver();
    stopCamera();

    return 0;
}
