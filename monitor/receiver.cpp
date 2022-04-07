/***********************************************
Sources:
https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2019-student-howtos/StreamOpenCVImages.pdf
https://github.com/derekmolloy/boneCV
***********************************************/

#define PORT 12345
#define MAX_LEN 1024

#include "receiver.h"
#include "camera.h"
static pthread_t receiverID;

static bool isShuttingDown = false;
static int socketDescriptor;
static struct sockaddr_in localSin;
static struct sockaddr_in remoteSin;

static void* receiverRunner(void* arg);

static void replyHandler(const char* command);
static void sendPing();
static void sendReply(const char* reply);

using namespace std;

void startReceiver() {
    memset(&localSin, 0, sizeof(localSin));
    localSin.sin_family = AF_INET; 
    localSin.sin_addr.s_addr = htonl(INADDR_ANY);
    localSin.sin_port = htons(PORT);
    socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    bind (socketDescriptor, (struct sockaddr*) &localSin, sizeof(localSin));
    pthread_create(&receiverID, NULL, receiverRunner, NULL);
}

void stopReceiver(void) {
    isShuttingDown = true;
    pthread_cancel(receiverID);
    pthread_join(receiverID, NULL);
    close(socketDescriptor);
}

void* receiverRunner(void* arg) {
    while(!isShuttingDown) {        
        char messageRx[MAX_LEN];
        unsigned int sinLen = sizeof(remoteSin);
        int bytesRx = recvfrom(socketDescriptor,
            messageRx, MAX_LEN - 1, 0,
            (struct sockaddr *) &remoteSin, &sinLen);
        messageRx[bytesRx] = '\0';

        replyHandler(messageRx);
    }

    return NULL;
}

static void replyHandler(const char* messageRx) {
    if(strncmp(messageRx, "test", MAX_LEN) == 0) {
        sendPing();
    }
    else if(strncmp(messageRx, "record", MAX_LEN) == 0) {
        startRecorder();
        sendReply("recording");
    }
    else if(strncmp(messageRx, "updateFrame", MAX_LEN) == 0) {
        updateFirstInitialFrame();
        sendReply("updating");
    }
    else if(strncmp(messageRx, "checkForMotion", MAX_LEN) == 0) {
        if (checkForMotion()) {
            sendReply("motion");
        }
        else {
            sendReply("noMotion");
        }
    }
}
    
static void sendReply(const char* reply) {
    int sinLen = sizeof(remoteSin);
    sendto(socketDescriptor,
    reply, strlen(reply),
    0,
    (struct sockaddr *) &remoteSin, sinLen);
}

static void sendPing() {
    sendReply("I do Baby Monitor things!");
}
