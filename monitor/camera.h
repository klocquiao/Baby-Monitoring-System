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

#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

void startCamera(void);
void stopCamera(void);

#endif