#if !defined(AFX_TEXTUREDLG_H__6E3E9C03_0910_11D3_A557_0020AFD8B8B6__INCLUDED_)
#define AFX_TEXTUREDLG_H__6E3E9C03_0910_11D3_A557_0020AFD8B8B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TextureDlg.h : header file
//
	enum {	
			Softgrain,
			Hardgrain,
			Coarseleather,
			Sandpaper,
			Loadtexture
		  };
	enum {	
			Fromtop,
			Frombottom,
			Fromright,
			Fromleft,
			Fromtopright,
			Fromtopleft,
			Fromlowright,
			Fromlowleft
		  };

/////////////////////////////////////////////////////////////////////////////
// CTextureDlg dialog

class CTextureDlg : public CDialog
{
// Construction
public:
	CTextureDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextureDlg)
	enum { IDD = IDD_FILTER_TEXTURIZE };
	int		m_nClass;
	int		m_nDirection;
	int		m_iContrast;
	//}}AFX_DATA
	CString	m_cstrFileName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextureDlg)
	afx_msg void OnClassChange();
	afx_msg void OnDirectionChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTUREDLG_H__6E3E9C03_0910_11D3_A557_0020AFD8B8B6__INCLUDED_)
