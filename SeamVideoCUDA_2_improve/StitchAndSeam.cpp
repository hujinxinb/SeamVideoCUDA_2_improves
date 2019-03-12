#include "StitchAndSeam.h"

#define BIG 1000000

//全局变量
bool g_flag = false;
Mat g_H;
Point g_leftTop, g_leftBottom, g_rightTop, g_rightBottom;
vector<int> g_seamLine;

//视频拼接
//void VideoStitch(string& str1, string& str2, string& str3)
//{
//	VideoCapture capture1(str1);
//	VideoCapture capture2(str2);
//	if (!capture1.isOpened() || !capture2.isOpened())
//	{
//		cout << "Error open capture1/capture2" << endl;
//		return;
//	}
//
//	Mat frame1, frame2, res;
//	capture1 >> frame1;
//	capture2 >> frame2;
//	if (!frame1.data || !frame2.data)
//	{
//		cout << "Error read" << endl;
//		return;
//	}
//	res = imageStitchForVideo(frame1, frame2);
//
//	int fps = (int)capture1.get(CV_CAP_PROP_FPS);            //获取视频帧率
//	int frameH = res.rows;//获取帧高度
//	int frameW = res.cols; //获取帧宽度 
//	int fourcc = (int)capture1.get(CV_CAP_PROP_FOURCC);      //获取视频格式
//	VideoWriter writer(str3, fourcc, fps, Size(frameW, frameH));
//
//	if (!writer.isOpened())
//	{
//		cout << "Error open writer" << endl;
//		return;
//	}
//	cout << "first" << endl;
//	imshow("res", res);
//	writer << res;
//
//	int i = 0;
//	while (waitKey(1) != ' ')
//	{
//		capture1 >> frame1;
//		capture2 >> frame2;
//		if (!frame1.data || !frame2.data)
//		{
//			cout << "Video Over" << endl;
//			return;
//		}
//		int start1 = clock();
//		res = imageStitchForVideoLater(frame1, frame2);
//		int start2 = clock();
//		cout << "total: " << start2 - start1 << endl;
//		writer << res;
//		imshow("res", res);
//	}
//	cout << "Video Over" << endl;
//}



void WriteYuv(string& str1,char* save)
{
	cv::VideoCapture vc;
	bool flag = vc.open(str1);
	if (!flag)
	{
		printf("avi file open error \n");
		system("pause");
		exit(-1);
	}

	int frmCount = vc.get(CV_CAP_PROP_FRAME_COUNT);
	frmCount -= 5;
	printf("frmCount: %d \n", frmCount);

	int w = vc.get(CV_CAP_PROP_FRAME_WIDTH);
	int h = vc.get(CV_CAP_PROP_FRAME_HEIGHT);
	int bufLen = w*h * 3 / 2;
	unsigned char* pYuvBuf = new unsigned char[bufLen];
	FILE* pFileOut = fopen(save, "w+");
	if (!pFileOut)
	{
		printf("pFileOut open error \n");
		system("pause");
		exit(-1);
	}
	printf("pFileOut open ok \n");

	for (int i = 0; i<frmCount; i++)
	{
		//printf("%d/%d \n", i + 1, frmCount);

		int start = clock();//计算开始时间

		cv::Mat srcImg;
		vc >> srcImg;

		cv::imshow("img", srcImg);
		cv::waitKey(1);

		cv::Mat yuvImg;
		cv::cvtColor(srcImg, yuvImg, CV_BGR2YUV_I420);
		memcpy(pYuvBuf, yuvImg.data, bufLen*sizeof(unsigned char));

		fwrite(pYuvBuf, bufLen*sizeof(unsigned char), 1, pFileOut);

		int end = clock();//计算结束时间



		printf("%d\n", end - start);
	}

	fclose(pFileOut);
	delete[] pYuvBuf;

}



void VideoStitch(char* str1, char* str2,int width, int height)
{
	int w = width;
	int h = height;
	//VideoCapture capture1(str1);


	int bufLen = w*h * 3 / 2;
	


	FILE* pFileIn1 = fopen(str1, "rb+");
	FILE* pFileIn2 = fopen(str2, "rb+");

	unsigned char* pYuvBuf1 = new unsigned char[bufLen];
	unsigned char* pYuvBuf2 = new unsigned char[bufLen];
	int iCount = 0;


	//下面这几行代码将yuv视频的帧数保存到all里
	fseek(pFileIn1, 0L, SEEK_END);
	long size = ftell(pFileIn1);
	int all = size / (w * h * 1.5);
	rewind(pFileIn1);
	

	

	fread(pYuvBuf1, bufLen*sizeof(unsigned char), 1, pFileIn1);
	fread(pYuvBuf2, bufLen*sizeof(unsigned char), 1, pFileIn2);



	cv::Mat yuvImg1;
	yuvImg1.create(h * 3 / 2, w, CV_8UC1);
	memcpy(yuvImg1.data, pYuvBuf1, bufLen*sizeof(unsigned char));
	cv::Mat rgbImg1;
	cv::cvtColor(yuvImg1, rgbImg1, CV_YUV2BGR_I420);


	cv::Mat yuvImg2;
	yuvImg2.create(h * 3 / 2, w, CV_8UC1);
	memcpy(yuvImg2.data, pYuvBuf2, bufLen*sizeof(unsigned char));
	cv::Mat rgbImg2;
	cv::cvtColor(yuvImg2, rgbImg2, CV_YUV2BGR_I420);


	int firstbegin = clock();//计算第一帧处理开始时间


	Mat res = imageStitchForVideo(rgbImg1, rgbImg2);


	int firstend = clock();//计算第一帧处理结束时间
	
	int frameH = res.rows;//获取帧高度
	int frameW = res.cols; //获取帧宽度 

	cout << "*****************" << firstend - firstbegin << "****************" << endl;
	cout << "*****************" << frameH << "****************" << endl;
	cout << "*****************" << frameW << "****************" << endl;
	
	int bufLens = frameW*frameH * 3 / 2;
	unsigned char* pYuvBufs = new unsigned char[bufLens];



		FILE* pFileOut = fopen("stitch.yuv", "w+");
		

		for (int i = 0; i<all; i++)
	{
		int start1 = clock();

		fread(pYuvBuf1, bufLen*sizeof(unsigned char), 1, pFileIn1);
		fread(pYuvBuf2, bufLen*sizeof(unsigned char), 1, pFileIn2);



		cv::Mat yuvImg1;
		yuvImg1.create(h * 3 / 2, w, CV_8UC1);
		memcpy(yuvImg1.data, pYuvBuf1, bufLen*sizeof(unsigned char));
		cv::Mat rgbImg1;
		cv::cvtColor(yuvImg1, rgbImg1, CV_YUV2BGR_I420);


		cv::Mat yuvImg2;
		yuvImg2.create(h * 3 / 2, w, CV_8UC1);
		memcpy(yuvImg2.data, pYuvBuf2, bufLen*sizeof(unsigned char));
		cv::Mat rgbImg2;
		cv::cvtColor(yuvImg2, rgbImg2, CV_YUV2BGR_I420);

		
		res = imageStitchForVideoLater(rgbImg1, rgbImg2);
		


		cv::Mat yuvImg;
		cv::cvtColor(res, yuvImg, CV_BGR2YUV_I420);
		memcpy(pYuvBufs, yuvImg.data, bufLens*sizeof(unsigned char));
		fwrite(pYuvBufs, bufLens*sizeof(unsigned char), 1, pFileOut);


		//writer << res;

		int start2 = clock();
		cout << "total: " << start2 - start1 << endl;
		imshow("res", res);
		cv::waitKey(1);
	}


	//	while (waitKey(1) != ' ')
	//	{
	//		capture1 >> frame1;
	//		capture2 >> frame2;
	//		if (!frame1.data || !frame2.data)
	//		{
	//			cout << "Video Over" << endl;
	//			return;
	//		}
	//		int start1 = clock();
	//		res = imageStitchForVideoLater(frame1, frame2);
	//		int start2 = clock();
	//		cout << "total: " << start2 - start1 << endl;
	//		writer << res;
	//		imshow("res", res);
	//	}

	delete[] pYuvBuf1;
	delete[] pYuvBuf2;
	delete[] pYuvBufs;
	
	fclose(pFileIn1);
	fclose(pFileIn2);
}






//视频图片第一次拼接
Mat imageStitchForVideo(Mat& frame1, Mat& frame2)
{
	Mat test, train;
	frame1.copyTo(test);
	frame2.copyTo(train);

	//灰度图转换  
	Mat test_gray, train_gray;
	cvtColor(test, test_gray, CV_BGR2GRAY);
	cvtColor(train, train_gray, CV_BGR2GRAY);

	//提取特征点    
	SurfFeatureDetector detector(80);  // 海塞矩阵阈值  
	vector<KeyPoint> test_keyPoint1, train_keyPoint2;
	detector.detect(test_gray, test_keyPoint1);
	detector.detect(train_gray, train_keyPoint2);

	//特征点描述，为下边的特征点匹配做准备    
	SurfDescriptorExtractor descriptor;
	Mat test_extractor1, train_extractor2;
	descriptor.compute(test_gray, test_keyPoint1, test_extractor1);
	descriptor.compute(train_gray, train_keyPoint2, train_extractor2);

	//得到训练器
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, train_extractor2);
	matcher.add(train_desc_collection);
	matcher.train();

	//匹配
	vector< vector< DMatch > > matches;
	matcher.knnMatch(test_extractor1, matches, 2);

	//获取有效匹配
	vector< DMatch > goodMatches;
//#pragma omp parallel for
	for (int i = 0; i<matches.size(); i++)
	{
		float dist1 = matches[i][0].distance;
		float dist2 = matches[i][1].distance;
		if (dist1<0.5*dist2)
			goodMatches.push_back(matches[i][0]);
	}

	//新特征点 
	vector<Point2f> test_keypoints1, train_keypoints2;
//#pragma omp parallel for
	for (int i = 0; i < goodMatches.size(); i++)
	{
		test_keypoints1.push_back(test_keyPoint1[goodMatches[i].queryIdx].pt);
		train_keypoints2.push_back(train_keyPoint2[goodMatches[i].trainIdx].pt);
	}

	bool flag = false;
	vector<vector<Point2f> > consensus;
	Mat H = computeHomography(train_keypoints2, test_keypoints1, 3, flag, consensus);   //自己的计算单应性矩阵方法
	g_flag = flag;
	H.copyTo(g_H);

	if (flag)
	{
		Point leftTop, leftBottom, rightTop, rightBottom;
		calcFourCorners(H, leftTop, leftBottom, rightTop, rightBottom, train);   //计算转换后四个角点
		g_leftTop = leftTop;
		g_leftBottom = leftBottom;
		g_rightTop = rightTop;
		g_rightBottom = rightBottom;

		Size sz = Size(MAX(MIN(rightTop.x, rightBottom.x), test.cols), MIN(test.rows, train.rows));
		Mat warp = Mat::zeros(sz, CV_8UC3), warp_temp;

		warpPerspective(train, warp, H, sz, 1, 0, Scalar(255, 255, 255));

		warp_temp = warp.clone();
		Rect rect(0, 0, MIN(leftTop.x, leftBottom.x), warp_temp.rows);
		if (rect.width>0 && rect.height>0)
			test(rect).copyTo(warp_temp(rect));//左边取自左图

		int start = MIN(leftTop.x, leftBottom.x);
		double processWidth = test.cols - start;
		Mat leftOverlap, rightOverlap;
		test(Rect(start, 0, processWidth, MIN(test.rows, train.rows))).copyTo(leftOverlap);
		warp_temp(Rect(start, 0, processWidth, MIN(test.rows, train.rows))).copyTo(rightOverlap);

		Mat overlap = seamCutting(leftOverlap, rightOverlap);
		overlap.copyTo(warp_temp(Rect(start, 0, processWidth, MIN(test.rows, train.rows))));

		return warp_temp;
	}
	else
	{
		int ht = MIN(test.rows, train.rows);
		Size sz(test.cols + train.cols, ht);
		Mat res = Mat::zeros(sz, CV_8UC3);
		test(Rect(0, 0, test.cols, ht)).copyTo(res(Rect(0, 0, test.cols, ht)));
		train(Rect(0, 0, train.cols, ht)).copyTo(res(Rect(test.cols, 0, train.cols, ht)));
		return res;
	}
}

//视频图片后续拼接
Mat imageStitchForVideoLater(Mat& frame1, Mat& frame2)
{
	GpuMat test_gpu, train_gpu;
	test_gpu.upload(frame1);
	train_gpu.upload(frame2);
	if (g_flag)
	{
		Size sz = Size(MAX(MIN(g_rightTop.x, g_rightBottom.x), test_gpu.cols), MIN(test_gpu.rows, train_gpu.rows));
		GpuMat warp_gpu;
		warpPerspective(train_gpu, warp_gpu, g_H, sz, 1, 0, Scalar(255, 255, 255));
		Rect rect(0, 0, MIN(g_leftTop.x, g_leftBottom.x), warp_gpu.rows);
		
		if (rect.width>0 && rect.height>0)
			test_gpu(rect).copyTo(warp_gpu(rect));//左边取自左图

		int start = MIN(g_leftTop.x, g_leftBottom.x);
		double processWidth = test_gpu.cols - start;
		GpuMat leftOverlap_gpu, rightOverlap_gpu;
		test_gpu(Rect(start, 0, processWidth, MIN(test_gpu.rows, train_gpu.rows))).copyTo(leftOverlap_gpu);
		warp_gpu(Rect(start, 0, processWidth, MIN(test_gpu.rows, train_gpu.rows))).copyTo(rightOverlap_gpu);

		GpuMat overlap = seamCuttingForVideo(leftOverlap_gpu, rightOverlap_gpu);

		overlap.copyTo(warp_gpu(Rect(start, 0, processWidth, MIN(test_gpu.rows, train_gpu.rows))));
		Mat warp;
		warp_gpu.download(warp);
		return warp;
	}
	else
	{
		int ht = MIN(test_gpu.rows, train_gpu.rows);
		Size sz(test_gpu.cols + train_gpu.cols, ht);
		GpuMat res_gpu(sz, CV_8UC3);
		test_gpu(Rect(0, 0, test_gpu.cols, ht)).copyTo(res_gpu(Rect(0, 0, test_gpu.cols, ht)));
		train_gpu(Rect(0, 0, train_gpu.cols, ht)).copyTo(res_gpu(Rect(test_gpu.cols, 0, train_gpu.cols, ht)));
		Mat res;
		res_gpu.download(res);
		return res;
	}
}

//seam GPU实现，在kernel.cu中实现
void seam_gpu(const GpuMat& src1, const GpuMat& src2, GpuMat& dst, const vector<int>& gseamLine, Stream& stream = Stream::Null());

//视频图片后续缝合线
GpuMat seamCuttingForVideo(GpuMat& leftOverlap_gpu, GpuMat& rightOverlap_gpu)
{
	GpuMat overlap_gpu;
	seam_gpu(leftOverlap_gpu, rightOverlap_gpu, overlap_gpu, g_seamLine);
	return overlap_gpu;
}

//缝合线融合
Mat seamCutting(Mat& leftOverlap, Mat& rightOverlap)
{
	int m = leftOverlap.cols;
	int n = leftOverlap.rows;

	//计算强度值strength=color^2+geometry
	Mat strength(n, m, CV_32FC1);
	Mat left_gray, right_gray;
	cvtColor(leftOverlap, left_gray, CV_BGR2GRAY);
	cvtColor(rightOverlap, right_gray, CV_BGR2GRAY);
	Mat grad_left_x, grad_left_y, grad_right_x, grad_right_y;
	Sobel(leftOverlap, grad_left_x, -1, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	Sobel(leftOverlap, grad_left_y, -1, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	Sobel(rightOverlap, grad_right_x, -1, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	Sobel(rightOverlap, grad_right_y, -1, 0, 1, 3, 1, 1, BORDER_DEFAULT);

//#pragma omp parallel for
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			int color = 0;
			int geometry = 0;
			for (int k = 0; k<3; k++)
			{
				color = color + leftOverlap.at<Vec3b>(i, j)[k] - rightOverlap.at<Vec3b>(i, j)[k];
				geometry = geometry + (grad_left_x.at<Vec3b>(i, j)[k] - grad_right_x.at<Vec3b>(i, j)[k])
					*(grad_left_y.at<Vec3b>(i, j)[k] - grad_right_y.at<Vec3b>(i, j)[k]);
			}
			strength.at<float>(i, j) = pow(color, 2) + geometry;
		}
	}
	//求缝合线
	vector<float> seam(m);
	vector<vector<int> > index(m, vector<int>(n, 0));
//#pragma omp parallel for
	for (int i = 0; i<m; i++)
	{
		seam[i] = strength.at<float>(0, i);
		index[i][0] = i;
	}
//#pragma omp parallel for
	for (int i = 1; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			int pre = index[j][i - 1];
			int a = strength.at<float>(i, pre);
			int b = pre - 1 >= 0 ? strength.at<float>(i, pre - 1) : BIG;
			int c = pre + 1<m ? strength.at<float>(i, pre + 1) : BIG;
			int mini = a, idx = pre;
			if (b<mini)
			{
				mini = b; idx = pre - 1;
			}
			if (c<mini)
			{
				mini = c; idx = pre + 1;
			}
			seam[j] = seam[j] + mini;
			index[j][i] = idx;
		}
	}
	int mini = seam[0]; int idx = 0;
//#pragma omp parallel for
	for (int i = 1; i<m; i++)
	{
		if (mini>seam[i])
		{
			mini = seam[i];
			idx = i;
		}
	}
	vector<int> seamLine = index[idx];
	g_seamLine = index[idx];
	Mat overlap;
	leftOverlap.copyTo(overlap);
//#pragma omp parallel for
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			if (j >= g_seamLine[i])
			{
				overlap.at<Vec3b>(i, j)[0] = rightOverlap.at<Vec3b>(i, j)[0];
				overlap.at<Vec3b>(i, j)[1] = rightOverlap.at<Vec3b>(i, j)[1];
				overlap.at<Vec3b>(i, j)[2] = rightOverlap.at<Vec3b>(i, j)[2];
			}
		}
	}
	return overlap;
}