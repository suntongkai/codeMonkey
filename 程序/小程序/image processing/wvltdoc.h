// WvltDoc.h : interface of the CWvltDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WVLTDOC_H__F604916E_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
#define AFX_WVLTDOC_H__F604916E_698F_11D2_A679_0020AFD8B8B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CWvltDoc : public CDocument
{
protected: // create from serialization only
	CWvltDoc();
	DECLARE_DYNCREATE(CWvltDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWvltDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWvltDoc();

	unsigned char* m_pBitmap;
	unsigned char* m_pTransfered;
	BOOL m_fDirty;
	CString m_strFileName;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL ReadBitmap(LPCTSTR lpszPathName, unsigned char*& buffer);
// Generated message map functions
protected:
	//{{AFX_MSG(CWvltDoc)
	afx_msg void OnFilterReverse();
	afx_msg void OnMenuitem32794();
	afx_msg void OnUpdateMenuitem32794(CCmdUI* pCmdUI);
	afx_msg void OnAverage();
	afx_msg void OnMid();
	afx_msg void OnSharp();
	afx_msg void OnDct();
	afx_msg void OnEdgeDetection();
	afx_msg void OnEdgeExtraction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WVLTDOC_H__F604916E_698F_11D2_A679_0020AFD8B8B6__INCLUDED_)
