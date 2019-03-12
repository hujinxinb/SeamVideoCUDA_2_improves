#ifndef STITCHANDSEAM_H
#define STITCHANDSEAM_H



#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <stdio.h>
#include <ctime>
#include <omp.h>

#include <opencv2\gpu\gpu.hpp>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <opencv2/gpu/stream_accessor.hpp>
#include "GetHomography.h"

using namespace std;
using namespace cv;
using namespace cv::gpu;

//avi转yuv
void WriteYuv(string& str1, char* save);
//视频拼接
void VideoStitch(char* str1, char* str2, int width, int height);
//视频图片第一次拼接
Mat imageStitchForVideo(Mat& frame1, Mat& frame2);
//视频图片后续拼接
Mat imageStitchForVideoLater(Mat& frame1, Mat& frame2);
//视频图片后续缝合线
GpuMat seamCuttingForVideo(GpuMat& leftOverlap_gpu, GpuMat& rightOverlap_gpu);
//缝合线融合
Mat seamCutting(Mat& leftOverlap, Mat& rightOverlap);

#endif