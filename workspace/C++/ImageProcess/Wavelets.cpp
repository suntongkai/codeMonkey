// Wavelets.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Wavelets.h"

#include "ImageView.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "WvltDoc.h"
#include "WvltView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWvltApp

BEGIN_MESSAGE_MAP(CWvltApp, CWinApp)
	//{{AFX_MSG_MAP(CWvltApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWvltApp construction

CWvltApp::CWvltApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWvltApp object
CWvltApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWvltApp initialization

BOOL CWvltApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	m_pWvltTemplate = new CMultiDocTemplate(
		IDR_WVLTSTYPE,
		RUNTIME_CLASS(CWvltDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CWvltView));
	AddDocTemplate(m_pWvltTemplate);
	m_pImageTemplate = new CMultiDocTemplate(
			IDR_IMAGETYPE,
			RUNTIME_CLASS(CWvltDoc),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CImageView));
	AddDocTemplate(m_pImageTemplate);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();
	
	m_nCmdShow|= SW_HIDE;
	m_nCmdShow&= ~SW_SHOW;

	return TRUE;

}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnMenuitem32793();
	afx_msg void OnUpdateMenuitem32793(CCmdUI* pCmdUI);
	afx_msg void OnMenuitem32794();
	afx_msg void OnUpdateMenuitem32794(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_COMMAND(ID_MENUITEM32793, OnMenuitem32793)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM32793, OnUpdateMenuitem32793)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CWvltApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWvltApp commands

CDocument* CWvltApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	CWvltDoc* pDoc = (CWvltDoc*)CWinApp::OpenDocumentFile(lpszFileName);
	if (pDoc == NULL)
		return NULL;

	CFrameWnd* pNewFrame = m_pImageTemplate->CreateNewFrame(pDoc, NULL);
	if (pNewFrame == NULL)
		return pDoc;

	m_pImageTemplate->InitialUpdateFrame(pNewFrame, pDoc);

	// Tile the two MDI children windows within the MDI frame window.
	ASSERT_KINDOF(CMDIChildWnd, pNewFrame);
	CMDIFrameWnd* pMDIFrameWnd = ((CMDIChildWnd*)pNewFrame)->GetMDIFrame();
	ASSERT(pMDIFrameWnd != NULL);
	pMDIFrameWnd->MDICascade(); 
	return pDoc;

}

void CWvltApp::OnFileOpen() 
{
	CFileDialog dlg( TRUE,NULL,NULL,
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("Bitmap (*.BMP)|*.BMP|"));
	if( dlg.DoModal()==IDOK )
	{
		CString cstrFileName = dlg.GetPathName();
		OpenDocumentFile(cstrFileName);
	}	
}


void CAboutDlg::OnMenuitem32793() 
{
MessageBox("fffff");
}

void CAboutDlg::OnUpdateMenuitem32793(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CAboutDlg::OnMenuitem32794() 
{
	// TODO: Add your command handler code here
	
}

void CAboutDlg::OnUpdateMenuitem32794(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


