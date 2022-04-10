<<<<<<< Updated upstream
#include <iostream>
#include <string>

#include "audio.h"
#include "camera.h"
=======
//#include "camera.h"
>>>>>>> Stashed changes
#include "receiver.h"

int main(int argc, const char *argv[]) {
<<<<<<< Updated upstream
    startCamera();
    Audio audio;
    startReceiver(&audio);
=======
    startReceiver();
    //startCamera();
>>>>>>> Stashed changes

    while (1) {
    };

    stopReceiver();
    //stopCamera();

    return 0;
}
