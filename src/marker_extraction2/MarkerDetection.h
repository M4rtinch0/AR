#pragma once

#include <vector>
#include <opencv/highgui.h>
#include "MarkerCommon.h"

using namespace std;

class CMarkerDetection
{
public:
	CMarkerDetection();
	~CMarkerDetection();

	void MarkerDetection(IplImage *src, IplImage *dest);
	void DrawResult(IplImage *src, sMarkerAreaInfo &marker);

private:
	bool IsQuadrangle(CvSeq *box1, CvSeq *box2);
	void FindQuadrangleRegion (CvSeq *contours, int level);
	IplImage *CreateMarkerImage (IplImage *img, sMarkerAreaInfo &marker);
	int FindMarker (IplImage *imgMarker);

public:
	vector<sMarkerImg *> _markerDB;
	vector<sMarkerAreaInfo> _markerDetect;
};
