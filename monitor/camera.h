#ifndef CAMERA_H
#define CAMERA_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <nadjieb/mjpeg_streamer.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <pthread.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

void startCamera(void);
void stopCamera(void);
void updateFirstInitialFrame(void);
bool getIsMotionDetected(void);

void startRecorder(void);
void stopRecorder(void);
bool getIsRecording(void);

#endif