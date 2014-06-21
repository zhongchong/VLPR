#ifndef utility_h
#define utility_h

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

//outer function
extern QImage MatToQImage(const cv::Mat& mat);
extern void showImg(cv::Mat image);
extern cv::Mat cvtImg(cv::Mat image);
extern cv::Mat Sobel(const cv::Mat& image);
extern void thres(cv::Mat& image);
extern bool morphology(cv::Mat& image);
extern cv::Mat gaussian(cv::Mat image);
extern int getElement(cv::Mat image,int i,int j);
extern bool setElement(cv::Mat image,int i,int j,int val);
extern cv::Mat getLocation(cv::Mat image,cv::Mat original);
extern void charDiv(cv::Mat image,cv::Mat car_char[]);
extern QString charRec(cv::Mat car_char[]);

//inner function
void getThres(cv::Mat image,int t,int& res);
int max(int a, int b);
int pro_char_Rec(cv::Mat A,cv::Mat B);
void img_show(cv::Mat image);

#endif