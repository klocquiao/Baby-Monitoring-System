/***********************************************
Sources:
https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2019-student-howtos/StreamOpenCVImages.pdf
https://github.com/derekmolloy/boneCV
***********************************************/



#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <unistd.h>


using namespace std;
using namespace cv;

int main() {

  // setup the camera settings (640x480 image)
  VideoCapture capture(0);

  capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

  if (!capture.isOpened()) {
    cout << "Failed to connect to the camera." << endl;
  }

  Mat frame;

  while (1) {
    // capture and process images from the webcam
    capture >> frame;
    
    if (frame.empty()) {
      cout << "Failed to capture an image" << endl;
      return 0;
    }

    std::vector<uchar> buff;

    // encode to jpg
    cv::imencode(".jpg", frame, buff);

    // write jpg to stdout so it can be piped
    fwrite(buff.data(), buff.size(), 1, stdout);
    fflush(stdout);
  }

  return 0;
}