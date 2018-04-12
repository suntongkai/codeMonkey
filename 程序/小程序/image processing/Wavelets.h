// Wavelets.h : main header file for the WAVELETS application
//

#if !defined(AFX_WAVELETS_H__F6049166_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
#define AFX_WAVELETS_H__F6049166_698F_11D2_A679_0020AFD8B8B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
/////////////////////////////////////////////////////////////////////////////
// CWvltApp:
// See Wavelets.cpp for the implementation of this class
//

class CWvltApp : public CWinApp
{
public:
	CWvltApp();
	CMultiDocTemplate* m_pImageTemplate;
	CMultiDocTemplate* m_pWvltTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWvltApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWvltApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVELETS_H__F6049166_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
