#include "receiver.h"
#include "camera.h"

int main(int argc, const char *argv[]) {
    startReceiver();
    startCamera();

    while(1) {};
    
    stopReceiver();
    stopCamera();
        
    return 0;
}