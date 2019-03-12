#include "GetHomography.h"
#include <ctime>

using namespace std;
using namespace cv;

//计算单应性矩阵
Mat computeHomography(vector<Point2f> src, vector<Point2f> dst, double err_tol, bool& flag, vector<vector<Point2f> >& consensus)
{
	int n = src.size(); int m = 4;//n点总数, m用于求模型的点数
	Mat M = Mat::zeros(3, 3, CV_8UC3);//单应性矩阵
	if (n<4)
		return M;
	double cur_err_rate, in_all = 0.25;//cur_err_rate 当前错误率, in_all内点占总数目的百分比
	//num_consensus当前一致集中元素个数
	//num_consensus_min一致集中允许的最小个数
	//num_consensus_max一致集中当前最多个数
	//iters迭代次数
	int i, num_consensus, num_consensus_min, num_consensus_max = 0, iters = 0;
	srand(time(0));

	double p_badxform = 0.01;
	num_consensus_min = calc_min_inliers(n, m, 0.1, p_badxform);

	cur_err_rate = pow(1.0 - pow(in_all, m), iters);
	i = 0;

	vector<vector<Point2f> > pointSet, sample, best_consensus;
	pointSet.push_back(src);
	pointSet.push_back(dst);
	while (cur_err_rate>p_badxform)
	{
		getSample(pointSet, m, sample);
		M = getHomoMatrix(sample);

		num_consensus = findConsensus(pointSet, consensus, M, err_tol);
		if (num_consensus>num_consensus_max)
		{
			best_consensus = consensus;
			num_consensus_max = num_consensus;
			in_all = (double)num_consensus_max / n;
		}
		cur_err_rate = pow(1.0 - pow(in_all, m), ++iters);
	}
	M = getHomoMatrix(best_consensus);
	num_consensus = findConsensus(pointSet, consensus, M, err_tol);
	M = getHomoMatrix(consensus);
	if (num_consensus_max >= num_consensus_min)
	{
		flag = true;
	}
	return M;
}

//计算四角顶点
void calcFourCorners(Mat& H, Point& leftTop, Point& leftBottom, Point& rightTop, Point& rightBottom, Mat& img2)
{
	double v2[] = { 0, 0, 1 };
	double v1[3];
	Mat V2(3, 1, CV_64FC1, v2);
	Mat V1(3, 1, CV_64FC1, v1);
	Mat zero = Mat::zeros(3, 1, CV_64FC1);
	gemm(H, V2, 1, zero, 1, V1);
	leftTop.x = cvRound(v1[0] / v1[2]);
	if (leftTop.x<0)
		leftTop.x = 0;
	leftTop.y = cvRound(v1[1] / v1[2]);
	if (leftTop.y<0)
		leftTop.y = 0;

	v2[0] = 0;
	v2[1] = img2.rows;
	V2 = Mat(3, 1, CV_64FC1, v2);
	V1 = Mat(3, 1, CV_64FC1, v1);
	gemm(H, V2, 1, zero, 1, V1);
	leftBottom.x = cvRound(v1[0] / v1[2]);
	if (leftBottom.x<0)
		leftBottom.x = 0;
	leftBottom.y = cvRound(v1[1] / v1[2]);
	if (leftBottom.y<0)
		leftBottom.y = 0;

	v2[0] = img2.cols;
	v2[1] = 0;
	V2 = Mat(3, 1, CV_64FC1, v2);
	V1 = Mat(3, 1, CV_64FC1, v1);
	gemm(H, V2, 1, zero, 1, V1);
	rightTop.x = cvRound(v1[0] / v1[2]);
	if (rightTop.x<0)
		rightTop.x = 0;
	rightTop.y = cvRound(v1[1] / v1[2]);
	if (rightTop.y<0)
		rightTop.y = 0;

	v2[0] = img2.cols;
	v2[1] = img2.rows;
	V2 = Mat(3, 1, CV_64FC1, v2);
	V1 = Mat(3, 1, CV_64FC1, v1);
	gemm(H, V2, 1, zero, 1, V1);
	rightBottom.x = cvRound(v1[0] / v1[2]);
	if (rightBottom.x<0)
		rightBottom.x = 0;
	rightBottom.y = cvRound(v1[1] / v1[2]);
	if (rightBottom.y<0)
		rightBottom.y = 0;
}

//计算要求的最少的一致性集中元素个数
int calc_min_inliers(int n, int m, double p_badsupp, double p_badxform)
{
	//根据论文：Chum, O. and Matas, J.  Matching with PROSAC -- Progressive Sample Consensus
	//中的一个公式计算，看不懂
	double pi, sum;
	int i, j;

	for (j = m + 1; j <= n; j++)
	{
		sum = 0;
		for (i = j; i <= n; i++)
		{
			pi = (i - m) * log(p_badsupp) + (n - i + m) * log(1.0 - p_badsupp) +
				log_factorial(n - m) - log_factorial(i - m) -
				log_factorial(n - i);
			/*
			* Last three terms above are equivalent to log( n-m choose i-m )
			*/
			sum += exp(pi);
		}
		if (sum < p_badxform)
			break;
	}
	return j;
}

//计算n的阶乘的自然对数
double log_factorial(int n)
{
	double f = 0;
	int i;

	for (i = 1; i <= n; i++)
		f += log(i);

	return f;
}

// 数据集point, 样本数量n, 样本集samp, 随机选取样本点
void getSample(vector< vector<Point2f> >& point, int n, vector< vector<Point2f> >& samp)
{
	vector<Point2f> point0 = point[0];
	vector<Point2f> point1 = point[1];
	vector<Point2f> samp0;
	vector<Point2f> samp1;
	int num = point0.size();
	samp.clear();

	vector<int> selected(num, 0);
	for (int i = 0; i<n; i++)
	{
		int ind;
		do
		{
			ind = rand() % num;
		} while (selected[ind]);
		selected[ind] = 1;
		samp0.push_back(point0[ind]);
		samp1.push_back(point1[ind]);
	}
	samp.push_back(samp0);
	samp.push_back(samp1);
}

//由样例计算单应矩阵
Mat getHomoMatrix(vector<vector<Point2f> >& sample)
{
	vector<Point2f> sample0 = sample[0];
	vector<Point2f> sample1 = sample[1];
	int num = sample0.size();

	Mat A = Mat::zeros(2 * num, 8, CV_64FC1);
	Mat B = Mat::zeros(2 * num, 1, CV_64FC1);
	Mat X = Mat::zeros(8, 1, CV_64FC1);

	for (int i = 0; i<num; i++)
	{
		A.at<double>(i, 0) = sample0[i].x;
		A.at<double>(i + num, 3) = sample0[i].x;
		A.at<double>(i, 1) = sample0[i].y;
		A.at<double>(i + num, 4) = sample0[i].y;
		A.at<double>(i, 2) = 1.0;
		A.at<double>(i + num, 5) = 1.0;
		A.at<double>(i, 6) = -sample0[i].x*sample1[i].x;
		A.at<double>(i, 7) = -sample0[i].y*sample1[i].x;
		A.at<double>(i + num, 6) = -sample0[i].x*sample1[i].y;
		A.at<double>(i + num, 7) = -sample0[i].y*sample1[i].y;
		B.at<double>(i, 0) = sample1[i].x;
		B.at<double>(i + num, 0) = sample1[i].y;
	}

	solve(A, B, X, DECOMP_SVD);

	Mat H = Mat::zeros(3, 3, CV_64FC1);
	H.at<double>(0, 0) = X.at<double>(0, 0); H.at<double>(0, 1) = X.at<double>(1, 0); H.at<double>(0, 2) = X.at<double>(2, 0);
	H.at<double>(1, 0) = X.at<double>(3, 0); H.at<double>(1, 1) = X.at<double>(4, 0); H.at<double>(1, 2) = X.at<double>(5, 0);
	H.at<double>(2, 0) = X.at<double>(6, 0); H.at<double>(2, 1) = X.at<double>(7, 0); H.at<double>(2, 2) = 1.0;

	return H;
}

//由单应性矩阵找出一致性集
int findConsensus(vector<vector<Point2f> >& point, vector<vector<Point2f> >& consensus, Mat H, double err_tol)
{
	consensus.clear();
	vector<Point2f> point0 = point[0];
	vector<Point2f> point1 = point[1];
	vector<Point2f> consensus0, consensus1;

	vector<Point2f> pd;
	perspectiveTransform(point0, pd, H);

	for (int i = 0; i<point0.size(); i++)
	{
		double err = sqrt(pow(point1[i].x - pd[i].x, 2) + pow(point1[i].y - pd[i].y, 2));
		if (err <= err_tol)
		{
			consensus0.push_back(point0[i]);
			consensus1.push_back(point1[i]);
		}
	}
	consensus.push_back(consensus0);
	consensus.push_back(consensus1);

	return consensus0.size();
}