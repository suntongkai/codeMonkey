// WvltView.h : interface of the CWvltView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WVLTVIEW_H__F6049170_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
#define AFX_WVLTVIEW_H__F6049170_698F_11D2_A679_0020AFD8B8B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWvltView : public CView
{
protected: // create from serialization only
	CWvltView();
	DECLARE_DYNCREATE(CWvltView)

// Attributes
public:
	CWvltDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWvltView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWvltView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CWvltView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WvltView.cpp
inline CWvltDoc* CWvltView::GetDocument()
   { return (CWvltDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WVLTVIEW_H__F6049170_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
