#ifndef GETHOMOGRAPHY_H
#define GETHOMOGRAPHY_H




#include <opencv2\core\core.hpp>
#include <vector>
//计算单应性矩阵
cv::Mat computeHomography(std::vector<cv::Point2f> src, std::vector<cv::Point2f> dst, double err_tol, bool& flag, std::vector<std::vector<cv::Point2f> >& consensus);
//计算四角顶点
void calcFourCorners(cv::Mat& H, cv::Point& leftTop, cv::Point& leftBottom, cv::Point& rightTop, cv::Point& rightBottom, cv::Mat& img2);
//计算要求的最少的一致性集中元素个数
int calc_min_inliers(int n, int m, double p_badsupp, double p_badxform);
//计算n的阶乘的自然对数
double log_factorial(int n);
// 数据集point, 样本数量n, 样本集samp, 随机选取样本点
void getSample(std::vector< std::vector<cv::Point2f> >& point, int n, std::vector< std::vector<cv::Point2f> >& samp);
//由样例计算单应矩阵
cv::Mat getHomoMatrix(std::vector<std::vector<cv::Point2f> >& sample);
//由单应性矩阵找出一致性集
int findConsensus(std::vector<std::vector<cv::Point2f> >& point, std::vector<std::vector<cv::Point2f> >& consensus, cv::Mat H, double err_tol);

#endif