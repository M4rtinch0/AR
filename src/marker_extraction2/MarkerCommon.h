#pragma once

#include <string>
#include <xutility>
#include <opencv/cv.h>

using namespace std;

struct sMarkerAreaInfo {
	CvPoint corner[4];
	int min_x, min_y;
	int max_x, max_y;

	void CalcSize()
	{
		min_x =  1000000; 
		min_y =  1000000;
		max_x = -1000000;
		max_y = -1000000;

		for (int i=0; i<4; ++i) {
			min_x = min(min_x, corner[i].x);
			max_x = max(max_x, corner[i].x);
			min_y = min(min_y, corner[i].y);
			max_y = max(max_y, corner[i].y);
		}
	}
};

struct sMarkerImg
{
	string name;
	double matching;

	CvMemStorage *storage;
	IplImage *gray;
	IplImage *image;
	CvSeq *contours;

	sMarkerImg (const char *fileName)
	{
		name = fileName;
		matching = 0.;

		storage = cvCreateMemStorage(0);

		image = cvLoadImage (fileName);
		gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

		cvCvtColor(image, gray, CV_RGB2GRAY);
		cvThreshold( gray, gray, 128, 255, CV_THRESH_BINARY_INV );

		cvFindContours (gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		cvDrawContours (image, contours, CV_RGB(255,255,0), CV_RGB(0,255,0), 10, 1, CV_AA);
	}

	~sMarkerImg ()
	{
		cvReleaseImage(&image);
		cvReleaseImage(&gray);
		cvReleaseMemStorage (&storage);
	}
};

