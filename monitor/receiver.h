#ifndef RECEIVER_H
#define RECEIVER_H

//#include "camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <fstream>

void startReceiver(void);
void stopReceiver(void);

#endif