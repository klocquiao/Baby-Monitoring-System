#include "recorder.h"
using namespace std;
using namespace cv;

#define RECORDING_LENGTH_SEC 30
static bool isStopping = false;

static pthread_t recorderID;
static pthread_mutex_t recorderMutex = PTHREAD_MUTEX_INITIALIZER;

static void* recorderRunner(void* arg);

void startRecorder() {
    pthread_create(&recorderID, NULL, recorderRunner, NULL);
    struct timespec reqDelay = {RECORDING_LENGTH_SEC, 0};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

void stopRecorder(void) {
    isStopping = true;
    pthread_join(recorderID, NULL);
}

void* recorderRunner(void* arg) {
    VideoCapture capture(0);
    capture.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

    VideoWriter output("bmRecording.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(FRAME_WIDTH, FRAME_HEIGHT));

    while(!isStopping) {
        Mat frame;

        capture >> frame;
        if (!capture.isOpened()) {
            cout << "Failed to connect to the camera." << endl;
            exit(0);
        }

        output.write(frame);
    }

  output.release();
  return NULL;
}            