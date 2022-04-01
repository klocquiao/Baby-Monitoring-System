#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <nadjieb/mjpeg_streamer.hpp>
#include <unistd.h>
#include <pthread.h>
#include <vector>

void startCamera(void);
void stopCamera(void);

#endif