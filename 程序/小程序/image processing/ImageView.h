#if !defined(AFX_IMAGEVIEW_H__F6049179_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
#define AFX_IMAGEVIEW_H__F6049179_698F_11D2_A679_0020AFD8B8B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImageView.h : header file
//
#include "WvltDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CImageView view

class CImageView : public CView
{
protected:
	CImageView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CImageView)

// Attributes
public:
	CWvltDoc* GetDocument();	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
inline CWvltDoc* CImageView::GetDocument()
   { return (CWvltDoc*)m_pDocument; }
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEW_H__F6049179_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
