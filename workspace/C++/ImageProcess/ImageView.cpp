// ImageView.cpp : implementation file
//

#include "stdafx.h"
#include "Wavelets.h"
#include "ImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNCREATE(CImageView, CView)

CImageView::CImageView()
{
}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CView)
	//{{AFX_MSG_MAP(CImageView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView drawing

void CImageView::OnDraw(CDC* pDC)
{
	CWvltDoc* pDoc = GetDocument();

	unsigned char* pBitmap = pDoc -> m_pBitmap;
	LPBITMAPINFO lpBitmapInfo = (LPBITMAPINFO)(pBitmap + 14);
	unsigned char* pBitmapData = pBitmap + ((LPBITMAPFILEHEADER)pBitmap)->bfOffBits;
	unsigned long biHeight = ((LPBITMAPINFOHEADER)lpBitmapInfo)->biHeight;
	unsigned long biWidth = ((LPBITMAPINFOHEADER)lpBitmapInfo)->biWidth;

	CRect rect;
	GetClientRect(&rect);
	long originx =0;
	long originy =0;
	if((unsigned long)(rect.Width()) > biWidth)
		originx = (rect.Width() - biWidth)>>1;
	if((unsigned long)(rect.Height()) > biHeight)
		originy = (rect.Height() - biHeight)>>1;
	SetDIBitsToDevice(pDC->m_hDC, originx, originy, biWidth, biHeight, 0, 0, 0, biHeight, pBitmapData, 
							lpBitmapInfo, DIB_RGB_COLORS);

}

/////////////////////////////////////////////////////////////////////////////
// CImageView diagnostics

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageView message handlers
BOOL CImageView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.cy = cs.cx =0;	
	return CView::PreCreateWindow(cs);
}

