#include "stdafx.h"
#include "Timer.h"
#include "log.h"
#include "MarkerDetection.h"

CMarkerDetection::CMarkerDetection()
{
	_markerDB.push_back(new sMarkerImg("a.bmp"));
	_markerDB.push_back(new sMarkerImg("b.bmp"));
	_markerDB.push_back(new sMarkerImg("c.bmp"));
	_markerDB.push_back(new sMarkerImg("d.bmp"));
	_markerDB.push_back(new sMarkerImg("e.bmp"));
	_markerDB.push_back(new sMarkerImg("f.bmp"));
	_markerDB.push_back(new sMarkerImg("g.bmp"));
	_markerDB.push_back(new sMarkerImg("h.bmp"));
}

CMarkerDetection::~CMarkerDetection()
{
	for (unsigned int i=0; i<_markerDB.size(); ++i) {
		delete _markerDB[i];
	}
}

void CMarkerDetection::DrawResult(IplImage *src, sMarkerAreaInfo &marker)
{
	CvScalar color = CV_RGB (255, 0, 0);

	cvLine (src, marker.corner[0], marker.corner[1], color, 2);
	cvLine (src, marker.corner[1], marker.corner[2], color, 2);
	cvLine (src, marker.corner[2], marker.corner[3], color, 2);
	cvLine (src, marker.corner[3], marker.corner[0], color, 2);

	cvLine (src, marker.corner[0], marker.corner[2], color, 2);
	cvLine (src, marker.corner[1], marker.corner[3], color, 2);
}

inline double perpendicular (CvPoint &l0, CvPoint &l1, CvPoint &p)
{
	double vx = l1.x - l0.x;
	double vy = l1.y - l0.y;
	double px = p.x - l0.x;
	double py = p.y - l0.y;
	double vl = sqrt(vx*vx + vy*vy);

	return (px*vy - py*vx) / vl;
}

bool CMarkerDetection::IsQuadrangle(CvSeq *box1, CvSeq *box2) 
{
	CvPoint p1[4];
	CvPoint p2[4];
	
	for (int i=0; i<4; ++i) {
		p1[i] = *(CvPoint *)cvGetSeqElem(box1, i);
		p2[i] = *(CvPoint *)cvGetSeqElem(box2, i);
	}

	double d[8] = {
		fabs(perpendicular(p1[0], p1[2], p2[0])),
		fabs(perpendicular(p1[0], p1[2], p2[1])),
		fabs(perpendicular(p1[0], p1[2], p2[2])),
		fabs(perpendicular(p1[0], p1[2], p2[3])),

		fabs(perpendicular(p1[1], p1[3], p2[0])),
		fabs(perpendicular(p1[1], p1[3], p2[1])),
		fabs(perpendicular(p1[1], p1[3], p2[2])),
		fabs(perpendicular(p1[1], p1[3], p2[3])),
	};

	const double threshold = 5;

	if (d[0] < threshold && d[2] < threshold && d[5] < threshold && d[7] < threshold) return true;
	if (d[1] < threshold && d[3] < threshold && d[4] < threshold && d[6] < threshold) return true;
	return false;
}

void CMarkerDetection::FindQuadrangleRegion (CvSeq *contours, int level)
{
	for (CvSeq *s = contours; s; s = s->h_next){
		if (level%2 == 0 && s->v_next && s->total == 4 && s->v_next->total == 4) {
			if (IsQuadrangle(s, s->v_next)) {
				sMarkerAreaInfo marker;
				marker.corner[0] = *(CvPoint *)cvGetSeqElem(s->v_next, 0);
				marker.corner[1] = *(CvPoint *)cvGetSeqElem(s->v_next, 1);
				marker.corner[2] = *(CvPoint *)cvGetSeqElem(s->v_next, 2);
				marker.corner[3] = *(CvPoint *)cvGetSeqElem(s->v_next, 3);
				
				marker.CalcSize ();

				_markerDetect.push_back (marker);
			}
		}

		if (s->v_next) {
			FindQuadrangleRegion (s->v_next, level+1);
		}
	}
}

void CMarkerDetection::MarkerDetection(IplImage *src, IplImage *dest)
{
	PERFORM("MarkerDetection()");

	IplImage *imgGray = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);

	cvCvtColor(src, imgGray, CV_RGB2GRAY);

	cvSmooth (imgGray, imgGray, CV_GAUSSIAN, 3, 3);

	IplImage *imgBinary = cvCreateImage (cvGetSize(imgGray), IPL_DEPTH_8U, 1);
	cvCopyImage (imgGray, imgBinary);

	// binary 이미지로 만든다.
	// 두 함수 중 하나를 골라 쓴다.
	//cvThreshold (imgBinary, imgBinary, 0.0, 255.0, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	cvAdaptiveThreshold(imgBinary,  imgBinary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 71, 15);

	//cvShowImage ("imgBinary", imgBinary);
	
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *contours = NULL;

	int noContour = cvFindContours (imgBinary, storage, &contours, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	// int noContour = cvFindContours (imgBinary, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	CvSeq *approxContours = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3., 1);
	// cvDrawContours (dest, approxContours, CV_RGB(255,255,0), CV_RGB(0,255,0), 10, 1, CV_AA);

	_markerDetect.clear ();
	FindQuadrangleRegion (approxContours, 0);

	for (unsigned int i=0; i<_markerDetect.size(); ++i) {
		IplImage *imgMarker = CreateMarkerImage (imgGray, _markerDetect[i]);

		int id = FindMarker (imgMarker);
		if (0 <= id) {
			cvShowImage ("find", _markerDB[id]->image);
		}

		cvReleaseImage (&imgMarker);

		DrawResult(dest, _markerDetect[i]);
	}

	cvReleaseMemStorage (&storage);
	cvReleaseImage(&imgBinary);
	cvReleaseImage(&imgGray);
}

int CMarkerDetection::FindMarker (IplImage *imgMarker)
{
	IplImage *imgMarkerColor = cvCreateImage (cvGetSize(imgMarker), IPL_DEPTH_8U, 3);

	cvCvtColor(imgMarker, imgMarkerColor, CV_GRAY2RGB);

	cvThreshold (imgMarker, imgMarker, 0.0, 255.0, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

	CvMemStorage *marker_storage = cvCreateMemStorage(0);
	CvSeq *mark_contour = NULL;

	cvFindContours (imgMarker, marker_storage, &mark_contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	cvDrawContours (imgMarkerColor, mark_contour, CV_RGB(255,255,0), CV_RGB(0,255,0), 10, 1, CV_AA);
	cvShowImage ("imgMarker", imgMarkerColor);

	double min_cp = 1e6;
	int min_id = -1;

	for (unsigned int j=0; j<_markerDB.size(); ++j) {
		double cp = cvMatchShapes (_markerDB[j]->contours, mark_contour, CV_CONTOURS_MATCH_I1);
		_markerDB[j]->matching = cp;

		if (cp < min_cp) {
			min_cp = cp;
			min_id = j;
		}
	}

	cvReleaseMemStorage (&marker_storage);
	cvReleaseImage (&imgMarkerColor);

	return min_id;
}

IplImage *CMarkerDetection::CreateMarkerImage (IplImage *img, sMarkerAreaInfo &marker) 
{
	assert (img->nChannels == 1);

	int dx = marker.max_x - marker.min_x + 1;
	int dy = marker.max_y - marker.min_y + 1;

	IplImage* imgSub = cvCreateImage (cvSize (dx, dy), IPL_DEPTH_8U, 1);

	cvSetZero (imgSub);

	for (int y = 0; y < dy; y++ ) {
		memcpy (&imgSub->imageData[y*imgSub->widthStep], &img->imageData[(y + marker.min_y)*img->widthStep + marker.min_x], dx);
	}	

	CvPoint2D32f srcQuad[4], dstQuad[4];
	CvMat *warp_matrix = cvCreateMat(3,3, CV_32FC1);

	IplImage *imgMarker = cvCreateImage (cvSize (100,100), IPL_DEPTH_8U, 1);
	cvZero(imgMarker);

	double dst_[4][2] = { { -5, -5}, { -5, 105}, { 105, 105}, { 105, -5} };

	for (int j=0; j<4; ++j) {
		srcQuad[j].x = (float)marker.corner[j].x - marker.min_x;
		srcQuad[j].y = (float)marker.corner[j].y - marker.min_y;
		dstQuad[j].x = (float)dst_[j][0];
		dstQuad[j].y = (float)dst_[j][1];
	}

	cvGetPerspectiveTransform (srcQuad, dstQuad, warp_matrix);
	cvWarpPerspective (imgSub, imgMarker, warp_matrix);

	cvReleaseImage (&imgSub);
	cvReleaseMat (&warp_matrix);

	return imgMarker;
}
