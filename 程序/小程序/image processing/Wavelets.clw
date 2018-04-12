; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wavelets.h"
LastPage=0

ClassCount=8
Class1=CChildFrame
Class2=CImageView
Class3=CMainFrame
Class4=CTextureDlg
Class5=CWvltApp
Class6=CAboutDlg
Class7=CWvltDoc
Class8=CWvltView

ResourceCount=3
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_WVLTSTYPE
Resource3=IDR_MAINFRAME (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CImageView]
Type=0
BaseClass=CView
HeaderFile=ImageView.h
ImplementationFile=ImageView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CTextureDlg]
Type=0
BaseClass=CDialog
HeaderFile=TextureDlg.h
ImplementationFile=TextureDlg.cpp

[CLS:CWvltApp]
Type=0
BaseClass=CWinApp
HeaderFile=Wavelets.h
ImplementationFile=Wavelets.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Wavelets.cpp
ImplementationFile=Wavelets.cpp
LastObject=IDM_FILTER_REVERSE
Filter=D
VirtualFilter=dWC

[CLS:CWvltDoc]
Type=0
BaseClass=CDocument
HeaderFile=wvltdoc.h
ImplementationFile=wvltdoc.cpp
Filter=N
VirtualFilter=DC
LastObject=IDM_SHARP

[CLS:CWvltView]
Type=0
BaseClass=CView
HeaderFile=WvltView.h
ImplementationFile=WvltView.cpp
LastObject=CWvltView

[DLG:IDD_FILTER_TEXTURIZE]
Type=1
Class=CTextureDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_WVLTSTYPE]
Type=1
Class=CAboutDlg
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=IDM_FILTER_REVERSE
Command6=IDM_AVERAGE
Command7=IDM_MID
Command8=IDM_SHARP
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_ARRANGE
Command12=ID_APP_ABOUT
Command13=IDM_DCT
Command14=ID_EDGEDETECTION
Command15=ID_EDGEEXTRACTION
CommandCount=15

