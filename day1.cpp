#include "stdafx.h"

#include <iostream>
#include <opencv2/core/core.hpp>   //cvGetSize  cvCreateImage
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>  //cvResize cvInitMatHeader cvGetMinMaxHistValue cvCvtColor
#include <opencv2/imgproc/imgproc.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_core244d")
#pragma comment(lib, "opencv_highgui244d")
#pragma comment(lib, "opencv_imgproc244d")  //cvResize
#else
#pragma comment(lib, "opencv_core244d")
#pragma comment(lib, "opencv_highgui244d")
#pragma comment(lib, "opencv_imgproc244d")  //cvResize
#endif
#define cvQueryHistValue_1D(hist,idx0) ((float)cvGetReal1D( (hist)->bins, (idx0)))

using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  
void FillWhite(IplImage* pImage)
{
	cvRectangle(pImage, cvPoint(0, 0), cvPoint(pImage->width, pImage->height), CV_RGB(255, 255, 255), CV_FILLED);
}
// 创建灰度图像的直方图  
CvHistogram* CreateGrayImageHist(IplImage** ppImage)
{
	int nHistSize = 256;
	float fRange[] = { 0, 255 };  //灰度级的范围    
	float* pfRanges[] = { fRange };
	CvHistogram* pcvHistogram = cvCreateHist(1, &nHistSize, CV_HIST_ARRAY, pfRanges);
	cvCalcHist(ppImage, pcvHistogram);
	return pcvHistogram;
}
// 根据直方图创建直方图图像  
IplImage* CreateHisogramImage(int nImageWidth, int nScale, int nImageHeight, CvHistogram* pcvHistogram)
{
	IplImage* pHistImage = cvCreateImage(cvSize(nImageWidth * nScale, nImageHeight), IPL_DEPTH_8U, 1);
	FillWhite(pHistImage);

	//统计直方图中的最大直方块  
	float fMaxHistValue = 0;
	cvGetMinMaxHistValue(pcvHistogram, NULL, &fMaxHistValue, NULL, NULL);

	//分别将每个直方块的值绘制到图中  
	int i;
	for (i = 0; i < nImageWidth; i++)
	{
		float fHistValue = cvQueryHistValue_1D(pcvHistogram, i); //像素为i的直方块大小  
		int nRealHeight = cvRound((fHistValue / fMaxHistValue) * nImageHeight);  //要绘制的高度  
		cvRectangle(pHistImage,
			cvPoint(i * nScale, nImageHeight - 1),
			cvPoint((i + 1) * nScale - 1, nImageHeight - nRealHeight),
			cvScalar(i, 0, 0, 0),
			CV_FILLED
		);
	}
	return pHistImage;
}
int main(int argc, char** argv)
{
	const char* pstrWindowsSrcTitle = "原图";
	const char* pstrWindowsGrayTitle = "灰度图";
	const char* pstrWindowsHistTitle = "直方图";
	const char* pstrWindowsGrayEqualizeTitle = "灰度图-均衡化后";
	const char* pstrWindowsHistEqualizeTitle = "直方图-均衡化后";

	// 从文件中加载原图  
	// IplImage *pSrcImage = cvLoadImage("./images/yangmi.jpg", CV_LOAD_IMAGE_UNCHANGED);  
	IplImage* pSrcImage = cvLoadImage("./images/beauty.png", CV_LOAD_IMAGE_UNCHANGED);
	IplImage* pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	IplImage* pGrayEqualizeImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);

	// 灰度图  
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
	// 直方图图像数据  
	int nHistImageWidth = 255;
	int nHistImageHeight = 150;
	int nScale = 2;

	// 灰度直方图及直方图图像  
	CvHistogram* pcvHistogram = CreateGrayImageHist(&pGrayImage);
	IplImage* pHistImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogram);

	// 均衡化 
	//函数功能：直方图均衡化，该函数能归一化图像亮度和增强对比度
	//第一个参数表示输入图像，必须为灰度图（8位，单通道图）
	//第二个参数表示输出图像
	//该函数采用如下法则对输入图像进行直方图均衡化：
		//1：计算输入图像的直方图H。
		//2：直方图归一化，因此直方块和为255。
		//3：计算直方图积分，H'(i) = Sum(H(j)) (0<=j<=i)。
		//4：采用H'作为查询表：dst(x, y) = H'(src(x, y))进行图像变换。
	cvEqualizeHist(pGrayImage, pGrayEqualizeImage);

	// 均衡化后的灰度直方图及直方图图像  
	CvHistogram* pcvHistogramEqualize = CreateGrayImageHist(&pGrayEqualizeImage);
	IplImage* pHistEqualizeImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogramEqualize);

	// 显示  
	cvNamedWindow(pstrWindowsSrcTitle);
	cvNamedWindow(pstrWindowsGrayTitle);
	cvNamedWindow(pstrWindowsGrayEqualizeTitle);
	cvNamedWindow(pstrWindowsHistTitle);
	cvNamedWindow(pstrWindowsHistEqualizeTitle);
	cvShowImage(pstrWindowsSrcTitle, pSrcImage);
	cvShowImage(pstrWindowsGrayTitle, pGrayImage);
	cvShowImage(pstrWindowsGrayEqualizeTitle, pGrayEqualizeImage);
	cvShowImage(pstrWindowsHistTitle, pHistImage);
	cvShowImage(pstrWindowsHistEqualizeTitle, pHistEqualizeImage);
	cvWaitKey(0);
	//回收资源代码…  
	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsGrayTitle);
	cvDestroyWindow(pstrWindowsGrayEqualizeTitle);
	cvDestroyWindow(pstrWindowsHistTitle);
	cvDestroyWindow(pstrWindowsHistEqualizeTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pGrayImage);
	cvReleaseImage(&pGrayEqualizeImage);
	cvReleaseImage(&pHistImage);
	cvReleaseImage(&pHistEqualizeImage);
	return 0;
}