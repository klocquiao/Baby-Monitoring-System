/***********************************************
Sources:
https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2019-student-howtos/StreamOpenCVImages.pdf
https://github.com/derekmolloy/boneCV
***********************************************/


#include "camera.h"
using namespace std;
using namespace cv;
using MJPEGStreamer = nadjieb::MJPEGStreamer;

static pthread_t cameraID;
static pthread_mutex_t cameraMutex = PTHREAD_MUTEX_INITIALIZER;
static void* cameraRunner(void* arg);
static bool isStopping = false;

void startCamera() {
    pthread_create(&cameraID, NULL, cameraRunner, NULL);
}

void stopCamera(void) {
    isStopping = true;
    pthread_join(cameraID, NULL);
}

void* cameraRunner(void* arg) {
  // setup the camera settings (640x480 image)
    MJPEGStreamer streamer;

    // By default 1 worker is used for streaming
    // if you want to use 4 workers:
    //      streamer.start(8080, 4);
    streamer.start(8084);

    VideoCapture capture(0);

    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);

    if (!capture.isOpened()) {
        cout << "Failed to connect to the camera." << endl;
        exit(0);
    }

    Mat frame;

  while (!isStopping) {

    // capture and process images from the webcam
    pthread_mutex_lock(&cameraMutex);
    {
        capture >> frame;
        
        if (frame.empty()) {
            cout << "Failed to capture an image" << endl;
            return 0;
        }

    vector<uchar> buff; 
    cv::imencode(".jpg", frame, buff);
    streamer.publish("/stream", std::string(buff.begin(), buff.end()));
    
    // write jpg to stdout so it can be piped
    //fwrite(buff.data(), buff.size(), 1, stdout);
    //fflush(stdout);
    }
    pthread_mutex_unlock(&cameraMutex);

  }

  streamer.stop();

  return NULL;
}




