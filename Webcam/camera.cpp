/***********************************************
Sources:
https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2019-student-howtos/StreamOpenCVImages.pdf
https://github.com/derekmolloy/boneCV
https://gist.github.com/six519/6d2beee53038ebe8abd98063abfdad86 
***********************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;

int main() {

  Mat frame, gray, frameDelta, thresh, firstFrame;
  vector<vector<Point> > cnts;
  VideoCapture camera(0); //open camera
  
  //set the video size to 512x288 to process faster
  camera.set(3, 512);
  camera.set(4, 288);

  sleep(3);
  camera.read(frame);

  //convert to grayscale and set the first frame
  cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
  GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);

  
  int k = 0;
  while(camera.read(frame)) {


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

    for(int i = 0; i< cnts.size(); i++) {
      // threshold checker, I believe higher number means less sensitive to movement
      if(contourArea(cnts[i]) < 1500) {
          continue;
      }
      
      // Motion has been detected - can call node server functions to alert parent
      putText(frame, "Motion Detected", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
    }

    /* Motion detection end */
      
    if(waitKey(1) == 27){
      //exit if ESC is pressed
      break;
    }

    /* Stream camera to stdout begin */

    std::vector<uchar> buff;
    // encode to jpg
    cv::imencode(".jpg", frame, buff);

    // write jpg to stdout so it can be piped
    fwrite(buff.data(), buff.size(), 1, stdout);
    fflush(stdout);
    
    /* Stream camera to stdout end */  
  }

  return 0;
}