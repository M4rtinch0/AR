
// marker_extraction2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "marker_extraction2.h"
#include "marker_extraction2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cmarker_extraction2Dlg dialog

Cmarker_extraction2Dlg::Cmarker_extraction2Dlg(CWnd *pParent /*=NULL*/)
	: CDialog(Cmarker_extraction2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	_camera = NULL;
	_markerDetect = NULL;
}

void Cmarker_extraction2Dlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmarker_extraction2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Cmarker_extraction2Dlg message handlers

BOOL Cmarker_extraction2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&_imgRect);
	GetDlgItem(IDC_STATIC_IMAGE)->DestroyWindow();
	ScreenToClient(&_imgRect);

	_camera = new CCamOpenCV();
	_markerDetect = new CMarkerDetection();

	SetTimer(1000, 30, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cmarker_extraction2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cmarker_extraction2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cmarker_extraction2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (_camera) {				
		IplImage *img = _camera->CaptureImage();	
		if (img) {
			IplImage *imgContour = cvCreateImage (cvGetSize(img), IPL_DEPTH_8U, 3);
			cvCopy(img, imgContour, 0);

			_markerDetect->MarkerDetection(img, imgContour);

			cvFlip (imgContour, imgContour);

			CDC *pDC = GetDC();
			_camera->DrawImage((BYTE *)imgContour->imageData, _imgRect.left, _imgRect.top, 
				_imgRect.Width(), _imgRect.Height(), _imgRect.Width(), _imgRect.Height(), pDC);
			
			for (unsigned int i=0; i<_markerDetect->_markerDB.size(); ++i) {
				char buf[1024];
				sprintf (buf, "%s - %10.3f                                   ", 
					_markerDetect->_markerDB[i]->name.c_str (),
					_markerDetect->_markerDB[i]->matching);

				pDC->TextOut (650, 30 + i*20, buf,strlen(buf));
			}
			
			ReleaseDC(pDC);

			cvReleaseImage(&imgContour);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void Cmarker_extraction2Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	if(_camera) delete _camera;
	if(_markerDetect) delete _markerDetect;
}