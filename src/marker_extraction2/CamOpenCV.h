#pragma once

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

//#pragma comment(lib,"cv210.lib")
//#pragma comment(lib,"cxcore210.lib")
//#pragma comment(lib,"highgui210.lib")

class CCamOpenCV
{
public:
	CCamOpenCV(int cameraID = -1, int width = -1, int height = -1);
	virtual ~CCamOpenCV(void);

	IplImage *CaptureImage ();

	BITMAPINFO *GetBitmapInfo (int cameraID = 0) { return &_bitmapInfo; }

	void DrawImage(const BYTE *sImg, int ori_X, int ori_Y, int ori_Width, int ori_Height, int ViewWidth, int ViewHeight, CDC *pDC);

private:
	void InitBitmapInfo (int img_width,	int img_height, int pixelByte);

private:
	BITMAPINFO _bitmapInfo;	
	CvCapture *_capture;	
};
