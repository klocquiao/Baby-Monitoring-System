#ifndef RECEIVER_H
#define RECEIVER_H

#include <algorithm>
#include <fstream>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

#include "audio.h"

void startReceiver(Audio *audio);
void stopReceiver(void);

#endif