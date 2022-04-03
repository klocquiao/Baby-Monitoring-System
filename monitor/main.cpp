#include "camera.h"
#include "receiver.h"

// Test program to convert a2d to wave.
int main(int argc, const char *argv[]) {
    startReceiver();
    startCamera();

    while (1) {
    };

    stopReceiver();
    stopCamera();

    return 0;
}