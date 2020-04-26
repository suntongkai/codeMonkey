// WvltView.cpp : implementation of the CWvltView class
//

#include "stdafx.h"
#include "Wavelets.h"

#include "WvltDoc.h"
#include "WvltView.h"
#include <math.h>
#include <conio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWvltView
IMPLEMENT_DYNCREATE(CWvltView, CView)

BEGIN_MESSAGE_MAP(CWvltView, CView)
	//{{AFX_MSG_MAP(CWvltView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWvltView construction/destruction

CWvltView::CWvltView()
{
	// TODO: add construction code here

}

CWvltView::~CWvltView()
{
}
/////////////////////////////////////////////////////////////////////////////
// CWvltView drawing

void CWvltView::OnDraw(CDC* pDC)
{
	CWvltDoc* pDoc = GetDocument();

	//	Display the transfered image
	if( pDoc->m_pTransfered == NULL)
		return ;

	unsigned char* pBitmap = pDoc -> m_pBitmap;
	LPBITMAPINFO lpBitmapInfo = (LPBITMAPINFO)(pBitmap + 14);
	unsigned char* pBitmapData = pDoc->m_pTransfered;
	unsigned long biHeight = ((LPBITMAPINFOHEADER)lpBitmapInfo)->biHeight;
	unsigned long biWidth = ((LPBITMAPINFOHEADER)lpBitmapInfo)->biWidth;

	CRect rect;
	GetClientRect(&rect);
	long originx = 0;
	long originy = 0;
	if((unsigned long)(rect.Width()) > biWidth)
		originx = (rect.Width() - biWidth)>>1;
	if((unsigned long)(rect.Height()) > biHeight)
		originy = (rect.Height() - biHeight)>>1;

	SetDIBitsToDevice(pDC->m_hDC, originx, originy, biWidth, biHeight, 0, 0, 0, biHeight,
					  pBitmapData, lpBitmapInfo, DIB_RGB_COLORS);
}

/////////////////////////////////////////////////////////////////////////////
// CWvltView diagnostics

#ifdef _DEBUG
void CWvltView::AssertValid() const
{
	CView::AssertValid();
}

void CWvltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWvltDoc* CWvltView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWvltDoc)));
	return (CWvltDoc*)m_pDocument;
}
#endif //_DEBUG

