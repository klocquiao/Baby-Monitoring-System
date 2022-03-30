#include <iostream>

#include "receiver.h"
#include "camera.h"

int main(int argc, const char *argv[]) {
    startReceiver();
    startCamera();

    while(1) {};
    
    stopReceiver();
    stopCamera();
    
    std::cout << "Our baby monitor is awesome\n";
    
    return 0;
}