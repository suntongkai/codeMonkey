// TextureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wavelets.h"
#include "TextureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureDlg dialog


CTextureDlg::CTextureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureDlg)
	m_nClass = Softgrain;
	m_nDirection = Fromtop;
	m_iContrast = 0;
	//}}AFX_DATA_INIT
	m_cstrFileName.LoadString(IDS_TEXTRUE_SOFTGRAIN);
}


void CTextureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureDlg)
	DDX_CBIndex(pDX, IDC_TEXTURE_COMBO_CLASS, m_nClass);
	DDX_CBIndex(pDX, IDC_TEXTURE_COMBO_DIRECTION, m_nDirection);
	DDX_Text(pDX, IDC_TEXTURE_CONTRAST, m_iContrast);
	DDV_MinMaxInt(pDX, m_iContrast, 0, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureDlg, CDialog)
	//{{AFX_MSG_MAP(CTextureDlg)
	ON_CBN_SELCHANGE(IDC_TEXTURE_COMBO_CLASS, OnClassChange)
	ON_CBN_SELCHANGE(IDC_TEXTURE_COMBO_DIRECTION, OnDirectionChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureDlg message handlers

void CTextureDlg::OnClassChange() 
{
	CDataExchange	getDX(this, TRUE);
	DDX_CBIndex(&getDX, IDC_TEXTURE_COMBO_CLASS, m_nClass);
	if(m_nClass == Loadtexture)
	{
		CFileDialog dlg( TRUE,NULL,NULL,
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("Texture (*.TEX)|*.TEX|Bitmap (*.BMP)|*.BMP"));
		if( dlg.DoModal()==IDOK )
			m_cstrFileName = dlg.GetPathName();
		else
		{
			m_nClass = Softgrain;
			CDataExchange putDX(this, FALSE);
			DDX_CBIndex(&putDX, IDC_TEXTURE_COMBO_CLASS, m_nClass);
		}
	}
}

void CTextureDlg::OnDirectionChange() 
{	
}
