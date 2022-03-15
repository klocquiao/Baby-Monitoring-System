#include <iostream>
#include "receiver.h"
int main(int argc, const char *argv[]) {
    startReceiver();
    while(1) {};
    stopReceiver();
    
    std::cout << "Our baby monitor is awesome\n";
    
    return 0;
}