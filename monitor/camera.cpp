<<<<<<< Updated upstream
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
#define FILE_PATH "/mnt/remote/saved/monitor_"
#define FILE_TYPE ".avi"

static pthread_t cameraID;
static pthread_t recorderID;
static pthread_t timerID;

static pthread_mutex_t camMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t recordMutex = PTHREAD_MUTEX_INITIALIZER;

static void* cameraRunner(void* arg);
static void* recorderRunner(void* arg);
static void* timerRunner(void* arg);

static VideoCapture camera(0);

static Mat frame;
static Mat gray; 
static Mat frameDelta;
static Mat thresh;
static Mat firstFrame;

static bool isCamStopping = false;
static bool isRecStopping = false;
static bool isMotionDetected = true;
static bool isRecording = false;

static pthread_cond_t okayToWriteFrame = PTHREAD_COND_INITIALIZER;
static bool isNewFrame = false;


void startCamera(void) {
    pthread_create(&cameraID, NULL, cameraRunner, NULL);
}

void stopCamera(void) {
    isCamStopping = true;
    pthread_join(cameraID, NULL);
}

void* cameraRunner(void* arg) {
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
            isNewFrame = true;
            pthread_cond_signal(&okayToWriteFrame);
        }
        pthread_mutex_unlock(&camMutex);

        // Convert current frame to grayscale
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(21, 21), 0);

        // Compute difference between first frame and current frame
        absdiff(firstFrame, gray, frameDelta);
        threshold(frameDelta, thresh, 25, 255, THRESH_BINARY);
        
        dilate(thresh, thresh, Mat(), Point(-1,-1), 2);
        findContours(thresh, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if (!isMotionDetected) {
            for (unsigned int i = 0; i < cnts.size(); i++) {
                if (contourArea(cnts[i]) >= 3500) {
                    isMotionDetected = true;
                    startRecorder();
                    break;
                }
            }
        }

        if (waitKey(1) == 27){
            break;
        }

        // Capture and process images from the webcam
        vector<uchar> buff; 
        cv::imencode(".jpg", frame, buff);
        streamer.publish("/stream", std::string(buff.begin(), buff.end()));
    }

    streamer.stop();
    return NULL;
}

// RECORDER
void startRecorder(void) {
    pthread_mutex_lock(&recordMutex);
    {
        if (!isRecording) {
            isRecording = true;
            isRecStopping = false;
            pthread_create(&recorderID, NULL, recorderRunner, NULL);
            pthread_create(&timerID, NULL, timerRunner, NULL);
        }
    }
    pthread_mutex_unlock(&recordMutex);

}

void stopRecorder(void) {
    isRecStopping = true;
    pthread_join(recorderID, NULL);
    
    pthread_mutex_lock(&recordMutex);
    {
        isRecording = false;
    }
    pthread_mutex_unlock(&recordMutex);

}

void* timerRunner(void* arg) {
    struct timespec reqDelay = {RECORDING_LENGTH_SEC, 0};
    nanosleep(&reqDelay, (struct timespec *) NULL);
    stopRecorder();

    return NULL;
}
=======
// /***********************************************
// Sources:
// https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2019-student-howtos/StreamOpenCVImages.pdf
// https://github.com/derekmolloy/boneCV
// ***********************************************/

// //#include "camera.h"
// using namespace std;
// using namespace cv;
// using MJPEGStreamer = nadjieb::MJPEGStreamer;

// static pthread_t cameraID;
// static void* cameraRunner(void* arg);
// static bool isStopping = false;

// void startCamera() {
//     pthread_create(&cameraID, NULL, cameraRunner, NULL);
// }

// void stopCamera(void) {
//     isStopping = true;
//     pthread_join(cameraID, NULL);
// }

// void* cameraRunner(void* arg) {
//   // setup the camera settings (640x480 image)
//   MJPEGStreamer streamer;
//   Mat frame, gray, frameDelta, thresh, firstFrame;
//   vector<vector<Point>> cnts;

//   streamer.start(8084);
//   VideoCapture camera(0);

//   camera.set(3, 512);
//   camera.set(4, 288);

//   sleep(3);
//   camera.read(frame);

//   cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
//   GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);

//   int k = 0;
//   while (!isStopping) {
//     camera.read(frame);
//     /* Motion detection begin */

//     // Updates what the initial frame that the current frame will be compared to
//     if(k == 100) {
//         cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
//         GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);

//         k = 0;
//     }

//     k++;

//     //convert current frame to grayscale
//     cvtColor(frame, gray, COLOR_BGR2GRAY);
//     GaussianBlur(gray, gray, Size(21, 21), 0);

//     //compute difference between first frame and current frame
//     absdiff(firstFrame, gray, frameDelta);
//     threshold(frameDelta, thresh, 25, 255, THRESH_BINARY);
      
//     dilate(thresh, thresh, Mat(), Point(-1,-1), 2);
//     findContours(thresh, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

//     for (unsigned int i = 0; i < cnts.size(); i++) {
//       // threshold checker, I believe higher number means less sensitive to movement
//       if(contourArea(cnts[i]) < 1500) {
//           continue;
//       }
      
//       // Motion has been detected - can call node server functions to alert parent
//       putText(frame, "Motion Detected", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
//     }

//     // capture and process images from the webcam
//     vector<uchar> buff; 
//     cv::imencode(".jpg", frame, buff);
//     streamer.publish("/stream", std::string(buff.begin(), buff.end()));
    
//   }

//   streamer.stop();

//   return NULL;
// }
>>>>>>> Stashed changes

void* recorderRunner(void* arg) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    ostringstream stringStreamForTime;
    stringStreamForTime << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    string timeStr = stringStreamForTime.str();

    VideoWriter output("/mnt/remote/saved/output_" + timeStr + ".avi", 
        VideoWriter::fourcc('M', 'J', 'P', 'G'), 7, Size(FRAME_WIDTH, FRAME_HEIGHT));

    while(!isRecStopping) {
        Mat recFrame;
        pthread_mutex_lock(&camMutex);
        {
            while (!isNewFrame) {
                pthread_cond_wait(&okayToWriteFrame, &camMutex);
            }
            recFrame = frame;
            isNewFrame = false;
        }
        pthread_mutex_unlock(&camMutex);

        output.write(frame);
    }
    
    output.release();
    return NULL;
}         

// OTHER
void updateFirstInitialFrame() {
    cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
    GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);
    isMotionDetected = false;
}

bool getIsMotionDetected() {
    if (isMotionDetected) {
        return true;
    }

    return false;
}

bool getIsRecording() {
    bool isRec = false;
    pthread_mutex_lock(&recordMutex);
    {
        if (isRecording) {
            isRec = true;
        }
    }
    pthread_mutex_unlock(&recordMutex);

    return isRec;
}

