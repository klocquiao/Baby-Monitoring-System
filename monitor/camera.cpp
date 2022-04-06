/***********************************************
Sources:
https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2019-student-howtos/StreamOpenCVImages.pdf
https://github.com/derekmolloy/boneCV
***********************************************/

#include "camera.h"
using namespace std;
using namespace cv;
using MJPEGStreamer = nadjieb::MJPEGStreamer;

#define RECORDING_LENGTH_SEC 15
#define FRAME_WIDTH 544
#define FRAME_HEIGHT 288

static pthread_t cameraID;
static pthread_t recorderID;
static pthread_t timerID;
static pthread_mutex_t camMutex = PTHREAD_MUTEX_INITIALIZER;

static void* cameraRunner(void* arg);
static void* recorderRunner(void* arg);
static void* timerRunner(void* arg);

static bool isCamStopping = false;
static bool isRecStopping = false;

static VideoCapture camera(0);

static Mat frame;
static Mat gray; 
static Mat frameDelta;
static Mat thresh;
static Mat firstFrame;

void startCamera(void) {
    pthread_create(&cameraID, NULL, cameraRunner, NULL);
}

void stopCamera(void) {
    isCamStopping = true;
    pthread_join(cameraID, NULL);
}

void updateFirstInitialFrame() {
  cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
  GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);
}

void* cameraRunner(void* arg) {
  // setup the camera settings (640x480 image)
  MJPEGStreamer streamer;
  vector<vector<Point>> cnts;

  streamer.start(8084);

  camera.set(3, FRAME_WIDTH);
  camera.set(4, FRAME_HEIGHT);

  sleep(3);
  camera.read(frame);

  updateFirstInitialFrame();

  while (!isCamStopping) {
    pthread_mutex_lock(&camMutex);
    {
      camera.read(frame);
    }
    pthread_mutex_unlock(&camMutex);

    /* Motion detection begin */
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
      if(contourArea(cnts[i]) < 3500) {
          continue;
      }
      
      // Motion has been detected - can call node server functions to alert parent
      putText(frame, "Motion Detected", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
    }

    if(waitKey(1) == 27){
      //exit if ESC is pressed
      break;
    }

    // capture and process images from the webcam
    vector<uchar> buff; 
    cv::imencode(".jpg", frame, buff);
    streamer.publish("/stream", std::string(buff.begin(), buff.end()));
    
  }

  streamer.stop();

  return NULL;
}

// RECORDER

void startRecorder(void) {
    pthread_create(&recorderID, NULL, recorderRunner, NULL);
    pthread_create(&timerID, NULL, timerRunner, NULL);
}

void stopRecorder(void) {
    isRecStopping = true;
    pthread_join(recorderID, NULL);
}

void* timerRunner(void* arg) {
  struct timespec reqDelay = {RECORDING_LENGTH_SEC, 0};
  nanosleep(&reqDelay, (struct timespec *) NULL);

  stopRecorder();
  return NULL;
}

void* recorderRunner(void* arg) {
    VideoWriter output("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 15, Size(FRAME_WIDTH, FRAME_HEIGHT));

    while(!isRecStopping) {
        Mat recFrame;

        pthread_mutex_lock(&camMutex);
        {
          camera.read(recFrame);
        }
        pthread_mutex_unlock(&camMutex);

        if (!camera.isOpened()) {
            cout << "Failed to connect to the camera." << endl;
            exit(0);
        }

        output.write(recFrame);
    }

  output.release();

  return NULL;
}         



