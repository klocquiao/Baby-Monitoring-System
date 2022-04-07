#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/tracking.hpp>
#include <nadjieb/mjpeg_streamer.hpp>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <iomanip>
#include <ctime>

#define FRAME_WIDTH 544
#define FRAME_HEIGHT 288

void startCamera(void);
void stopCamera(void);
void updateFirstInitialFrame(void);
bool checkForMotion(void);

void startRecorder(void);
void stopRecorder(void);

#endif