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
// �����Ҷ�ͼ���ֱ��ͼ  
CvHistogram* CreateGrayImageHist(IplImage** ppImage)
{
	int nHistSize = 256;
	float fRange[] = { 0, 255 };  //�Ҷȼ��ķ�Χ    
	float* pfRanges[] = { fRange };
	CvHistogram* pcvHistogram = cvCreateHist(1, &nHistSize, CV_HIST_ARRAY, pfRanges);
	cvCalcHist(ppImage, pcvHistogram);
	return pcvHistogram;
}
// ����ֱ��ͼ����ֱ��ͼͼ��  
IplImage* CreateHisogramImage(int nImageWidth, int nScale, int nImageHeight, CvHistogram* pcvHistogram)
{
	IplImage* pHistImage = cvCreateImage(cvSize(nImageWidth * nScale, nImageHeight), IPL_DEPTH_8U, 1);
	FillWhite(pHistImage);

	//ͳ��ֱ��ͼ�е����ֱ����  
	float fMaxHistValue = 0;
	cvGetMinMaxHistValue(pcvHistogram, NULL, &fMaxHistValue, NULL, NULL);

	//�ֱ�ÿ��ֱ�����ֵ���Ƶ�ͼ��  
	int i;
	for (i = 0; i < nImageWidth; i++)
	{
		float fHistValue = cvQueryHistValue_1D(pcvHistogram, i); //����Ϊi��ֱ�����С  
		int nRealHeight = cvRound((fHistValue / fMaxHistValue) * nImageHeight);  //Ҫ���Ƶĸ߶�  
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
	const char* pstrWindowsSrcTitle = "ԭͼ";
	const char* pstrWindowsGrayTitle = "�Ҷ�ͼ";
	const char* pstrWindowsHistTitle = "ֱ��ͼ";
	const char* pstrWindowsGrayEqualizeTitle = "�Ҷ�ͼ-���⻯��";
	const char* pstrWindowsHistEqualizeTitle = "ֱ��ͼ-���⻯��";

	// ���ļ��м���ԭͼ  
	// IplImage *pSrcImage = cvLoadImage("./images/yangmi.jpg", CV_LOAD_IMAGE_UNCHANGED);  
	IplImage* pSrcImage = cvLoadImage("./images/beauty.png", CV_LOAD_IMAGE_UNCHANGED);
	IplImage* pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	IplImage* pGrayEqualizeImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);

	// �Ҷ�ͼ  
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
	// ֱ��ͼͼ������  
	int nHistImageWidth = 255;
	int nHistImageHeight = 150;
	int nScale = 2;

	// �Ҷ�ֱ��ͼ��ֱ��ͼͼ��  
	CvHistogram* pcvHistogram = CreateGrayImageHist(&pGrayImage);
	IplImage* pHistImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogram);

	// ���⻯ 
	//�������ܣ�ֱ��ͼ���⻯���ú����ܹ�һ��ͼ�����Ⱥ���ǿ�Աȶ�
	//��һ��������ʾ����ͼ�񣬱���Ϊ�Ҷ�ͼ��8λ����ͨ��ͼ��
	//�ڶ���������ʾ���ͼ��
	//�ú����������·��������ͼ�����ֱ��ͼ���⻯��
		//1����������ͼ���ֱ��ͼH��
		//2��ֱ��ͼ��һ�������ֱ�����Ϊ255��
		//3������ֱ��ͼ���֣�H'(i) = Sum(H(j)) (0<=j<=i)��
		//4������H'��Ϊ��ѯ��dst(x, y) = H'(src(x, y))����ͼ��任��
	cvEqualizeHist(pGrayImage, pGrayEqualizeImage);

	// ���⻯��ĻҶ�ֱ��ͼ��ֱ��ͼͼ��  
	CvHistogram* pcvHistogramEqualize = CreateGrayImageHist(&pGrayEqualizeImage);
	IplImage* pHistEqualizeImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogramEqualize);

	// ��ʾ  
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
	//������Դ���롭  
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