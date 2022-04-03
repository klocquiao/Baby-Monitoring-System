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
  Mat frame, gray, frameDelta, thresh, firstFrame;
  vector<vector<Point>> cnts;

  streamer.start(8084);
  VideoCapture camera(0);

  camera.set(3, 512);
  camera.set(4, 288);

  sleep(3);
  camera.read(frame);

  cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
  GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);

  int k = 0;
  while (!isStopping) {
    camera.read(frame);
    /* Motion detection begin */

    // Updates what the initial frame that the current frame will be compared to
    if(k == 100) {
        cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
        GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);

        k = 0;
    }

    k++;

    //convert current frame to grayscale
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(21, 21), 0);

    //compute difference between first frame and current frame
    absdiff(firstFrame, gray, frameDelta);
    threshold(frameDelta, thresh, 25, 255, THRESH_BINARY);
      
    dilate(thresh, thresh, Mat(), Point(-1,-1), 2);
    findContours(thresh, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (unsigned int i = 0; i < cnts.size(); i++) {
      // threshold checker, I believe higher number means less sensitive to movement
      if(contourArea(cnts[i]) < 1500) {
          continue;
      }
      
      // Motion has been detected - can call node server functions to alert parent
      putText(frame, "Motion Detected", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
    }

    // capture and process images from the webcam
    vector<uchar> buff; 
    cv::imencode(".jpg", frame, buff);
    streamer.publish("/stream", std::string(buff.begin(), buff.end()));
    
  }

  streamer.stop();

  return NULL;
}




