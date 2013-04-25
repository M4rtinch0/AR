
// marker_extraction2Dlg.h : header file
//

#pragma once

#include "CamOpenCV.h"
#include "MarkerDetection.h"

// Cmarker_extraction2Dlg dialog
class Cmarker_extraction2Dlg : public CDialog
{
// Construction
public:
	Cmarker_extraction2Dlg(CWnd *pParent = NULL);	// standard constructor

	CCamOpenCV *_camera;
	CMarkerDetection  *_markerDetect;
	CRect _imgRect;

// Dialog Data
	enum { IDD = IDD_marker_extraction2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
