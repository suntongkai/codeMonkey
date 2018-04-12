// WvltDoc.cpp : implementation of the CWvltDoc class
//

#include "stdafx.h"
#include "Wavelets.h"
#include "WvltDoc.h"
#include "TextureDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWvltDoc

IMPLEMENT_DYNCREATE(CWvltDoc, CDocument)

BEGIN_MESSAGE_MAP(CWvltDoc, CDocument)
	//{{AFX_MSG_MAP(CWvltDoc)
	ON_COMMAND(IDM_FILTER_REVERSE, OnFilterReverse)
	ON_COMMAND(IDM_AVERAGE, OnAverage)
	ON_COMMAND(IDM_MID, OnMid)
	ON_COMMAND(IDM_SHARP, OnSharp)
	ON_COMMAND(IDM_DCT, OnDct)
	ON_COMMAND(ID_EDGEDETECTION, OnEdgeDetection)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_EDGEEXTRACTION, OnEdgeExtraction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWvltDoc construction/destruction

CWvltDoc::CWvltDoc()
{
	m_fDirty = FALSE;
	m_pBitmap = NULL ;
	m_pTransfered = NULL;
}

CWvltDoc::~CWvltDoc()
{
	if( m_pBitmap != NULL)
		free( m_pBitmap);
	if( m_pTransfered != NULL)
		free( m_pTransfered	);
}

/////////////////////////////////////////////////////////////////////////////
// CWvltDoc serialization

void CWvltDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWvltDoc diagnostics

#ifdef _DEBUG
void CWvltDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWvltDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWvltDoc commands

BOOL CWvltDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CWvltDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	m_strFileName = lpszPathName;
	if (ReadBitmap(lpszPathName, m_pBitmap))
		UpdateAllViews(NULL);
	return TRUE;
}

BOOL CWvltDoc::ReadBitmap(LPCTSTR lpszPathName, unsigned char *& buffer)
{
	FILE *file;
	file = fopen( lpszPathName, "rb");
	if(!file)
		return FALSE;
	fpos_t posend, posbegin;

	fseek(file, 0, SEEK_END);
	fgetpos(file, &posend);
	fseek(file, 0, SEEK_SET);
	fgetpos(file,&posbegin);
	size_t filesize = (size_t)(posend - posbegin);
	
	if( buffer == NULL )
		buffer = (unsigned char*)malloc( filesize);
	if( buffer == NULL )
	{
		AfxMessageBox(IDM_MEMORY_INSUFFICIENT, MB_OK, 0);
		return FALSE;
	}
	memset(buffer, 0, filesize);
	size_t sizeread = fread(buffer, sizeof(unsigned char), filesize, file);
	if(sizeread != filesize)
	{
		AfxMessageBox(IDM_READFILE_ERROR, MB_OK, 0);
		free(buffer);
		buffer = NULL;
		fclose(file);
		return FALSE;
	}
	if( buffer[0] != 'B'||buffer[1] != 'M')
	{
		AfxMessageBox(IDM_FILEFORMAT_ERROR, MB_OK, 0);
		free(buffer);
		buffer = NULL;
		fclose(file);
		return FALSE;
	}
	fclose(file);
	return TRUE;
}



void CWvltDoc::OnFilterReverse() 
{
	//Preparation for the image's processing. After it the source image is pointed 
	//by lpData, and the destination image is pointed by m_pTransfered.
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;

	//Add the processing code here, which reverses the color of each pixel.
	int x, y, cur;
	for (y = 0; y < (int)biHeight; y++)
	{
		for (x = 0; x < (int)biWidth; x++)
		{
			cur = y*biAlign+3*x;	//current pixel
			m_pTransfered[cur]   = 255-lpData[cur];		//on B
			m_pTransfered[cur+1] = 255-lpData[cur+1];	//on G
			m_pTransfered[cur+2] = 255-lpData[cur+2];	//on R
		}
	}

	UpdateAllViews(NULL);	
}





void CWvltDoc::OnMenuitem32794() 
{
	// TODO: Add your command handler code here
	
}

void CWvltDoc::OnUpdateMenuitem32794(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CWvltDoc::OnAverage() 
{
	// TODO: Add your command handler code here
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;
	int x,y,cur;
	unsigned char *old;//存储改变之前的值
	old=(unsigned char*)malloc(bmSize);
	int cur00,cur01,cur02,cur10,cur12,cur20,cur21,cur22;
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			old[cur]=lpData[cur];
			old[cur+1]=lpData[cur+1];
			old[cur+2]=lpData[cur+2];
		}
	}
	for(y=0;y<(int)biHeight;y++)//3*3Box模板
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			m_pTransfered[cur]=(old[cur00]+old[cur01]+old[cur02]+
				old[cur10]+old[cur]+old[cur12]+
				old[cur20]+old[cur21]+old[cur22])/9;
			m_pTransfered[cur+1]=(old[cur00+1]+old[cur01+1]+old[cur02+1]+
				old[cur10+1]+old[cur+1]+old[cur12+1]+
				old[cur20+1]+old[cur21+1]+old[cur22+1])/9;
			m_pTransfered[cur+2]=(lpData[cur00+2]+old[cur01+2]+old[cur02+2]+
				old[cur10+2]+old[cur+2]+old[cur12+2]+
				old[cur20+2]+old[cur21+2]+old[cur22+2])/9;
		}
	}
	UpdateAllViews(NULL);
}

void CWvltDoc::OnMid() 
{
	// TODO: Add your command handler code here
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;
	int x,y,cur;
	unsigned char *old;//存储改变之前的值
	old=(unsigned char*)malloc(bmSize);
	unsigned char *swap;//存储用于排序的值
	swap=(unsigned char*)malloc(9);
	int flag[9];//记录下标
	char temp;//交换的中间变量
	int _temp;//交换的中间变量
	int i,j;//计数器
	int cur00,cur01,cur02,cur10,cur12,cur20,cur21,cur22;
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			old[cur]=lpData[cur];
			old[cur+1]=lpData[cur+1];
			old[cur+2]=lpData[cur+2];
		}
	}
	for(y=0;y<(int)biHeight-1;y++)//3*3模板
	{
		for(x=0;x<(int)biWidth-1;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			swap[0]=(old[cur00]+old[cur00+1]+old[cur00+2])/3;
			swap[1]=(old[cur01]+old[cur01+1]+old[cur01+2])/3;
			swap[2]=(old[cur02]+old[cur02+1]+old[cur02+2])/3;
			swap[3]=(old[cur10]+old[cur10+1]+old[cur10+2])/3;
			swap[4]=(old[cur]+old[cur+1]+old[cur+2])/3;
			swap[5]=(old[cur12]+old[cur12+1]+old[cur12+2])/3;
			swap[6]=(old[cur20]+old[cur20+1]+old[cur20+2])/3;
			swap[7]=(old[cur21]+old[cur21+1]+old[cur21+2])/3;
			swap[8]=(old[cur22]+old[cur22+1]+old[cur22+2])/3;
			flag[0]=cur00;
			flag[1]=cur01;
			flag[2]=cur02;
			flag[3]=cur10;
			flag[4]=cur;
			flag[5]=cur12;
			flag[6]=cur20;
			flag[7]=cur21;
			flag[8]=cur22;
			for(i=0;i<9;i++)
			{
				for(j=0;j<9-i-1;j++)
				{
					if(swap[j]>swap[j+1])
					{
						temp=swap[j];
						swap[j]=swap[j+1];
						swap[j+1]=temp;
						_temp=flag[j];
						flag[j]=flag[j+1];
						flag[j+1]=_temp;
					}
				}
			}
			m_pTransfered[cur]=old[flag[4]];
			m_pTransfered[cur+1]=old[flag[4]+1];
			m_pTransfered[cur+2]=old[flag[4]+2];
		}
	}
	UpdateAllViews(NULL);
}

void CWvltDoc::OnSharp()
{
	// TODO: Add your command handler code here
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;
	int x,y,cur;
	unsigned char *old;//存储改变之前的值
	old=(unsigned char*)malloc(bmSize);
	int cur00,cur01,cur02,cur10,cur12,cur20,cur21,cur22;
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			old[cur]=lpData[cur];
			old[cur+1]=lpData[cur+1];
			old[cur+2]=lpData[cur+2];
		}
	}
	for(y=0;y<(int)biHeight;y++)//拉普拉斯算子8
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			m_pTransfered[cur]=old[cur00]*-1+old[cur01]*-1+old[cur02]*-1+
				old[cur10]*-1+old[cur]*8+old[cur12]*-1+
				old[cur20]*-1+old[cur21]*-1+old[cur22]*-1;
			m_pTransfered[cur+1]=old[cur00+1]*-1+old[cur01+1]*-1+old[cur02+1]*-1+
				old[cur10+1]*-1+old[cur+1]*8+old[cur12+1]*-1+
				old[cur20+1]*-1+old[cur21+1]*-1+old[cur22+1]*-1;
			m_pTransfered[cur+2]=old[cur00+2]*-1+old[cur01+2]*-1+old[cur02+2]*-1+
				old[cur10+2]*-1+old[cur+2]*8+old[cur12+2]*-1+
				old[cur20+2]*-1+old[cur21+2]*-1+old[cur22+2]*-1;
		}
	}
	UpdateAllViews(NULL);
}

void CWvltDoc::OnDct() 
{
	// TODO: Add your command handler code here
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;
	double Cu,Cv;
	int u,v,x,y,i,j,k;//计数器
	int cur;
	char **f,**g_row,**g_column,**F_row,**F_column,**F_rowT,**F_columnT;
	f=new char *[(int)biWidth];
	for(i=0;i<(int)biWidth;i++)
		f[i]=new char[(int)biHeight];
	g_row=new char *[(int)biWidth];
	for(i=0;i<(int)biWidth;i++)
		g_row[i]=new char[(int)biWidth];
	g_column=new char *[(int)biHeight];
	for(i=0;i<(int)biHeight;i++)
		g_column[i]=new char[(int)biHeight];
	F_row=new char *[(int)biWidth];
	for(i=0;i<(int)biWidth;i++)
		F_row[i]=new char[(int)biHeight];
	F_column=new char *[(int)biHeight];
	for(i=0;i<(int)biHeight;i++)
		F_column[i]=new char[(int)biWidth];
	F_rowT=new char *[(int)biHeight];
	for(i=0;i<(int)biHeight;i++)
		F_rowT[i]=new char[(int)biWidth];
	F_columnT=new char *[(int)biWidth];
	for(i=0;i<(int)biWidth;i++)
		F_columnT[i]=new char[(int)biHeight];
	for(y=0;y<(int)biHeight;y++)//f(x,y)M*N
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			f[x][y]=lpData[cur];
		}
	}
	for(u=0;u<(int)biWidth;u++)//g_rowM*M
	{
		for(x=0;x<(int)biWidth;x++)
		{
		    if(u!=0)
			{Cu=1;}
		    else
			{Cu=1/sqrt(2);}
		    g_row[u][x]=Cu*sqrt(2/biWidth)*cos((2*x+1)*u*3.14/(2*biWidth));
		}
	}
	for(y=0;y<(int)biHeight;y++)//F_rowM*N
	{
		for(x=0;x<(int)biWidth;x++)
		{
			F_row[x][y]=0;
		}
	}
	for(y=0;y<(int)biHeight;y++)//F_rowM*N
	{
		for(x=0;x<(int)biWidth;x++)
		{
			for(i=0;i<(int)biHeight;i++)
			{
				F_row[x][y]=F_row[x][y]+g_row[x][i]*f[i][y];
			}
		}
	}
	for(i=0;i<(int)biWidth;i++)//转置N*M
	{
		for(j=0;j<(int)biHeight;j++)
		{
		    F_rowT[j][i]=F_row[i][j];
		}
	}
	for(v=0;v<(int)biHeight;v++)//g_columnN*N
	{
		for(y=0;y<(int)biHeight;y++)
		{
		    if(v!=0)
			{Cv=1;}
		    else
			{Cv=1/sqrt(2);}
		    g_column[v][y]=Cv*sqrt(2/biHeight)*cos((2*y+1)*v*3.14/(2*biHeight));
		}
	}
	for(j=0;j<(int)biWidth;j++)//F_columnN*M
	{
		for(i=0;i<(int)biHeight;i++)
		{
			F_column[i][j]=0;
		}
	}
	for(i=0;i<(int)biHeight;i++)//F_columnN*M
	{
		for(j=0;j<(int)biWidth;j++)
		{
			for(k=0;k<(int)biHeight;k++)
			{
				F_column[i][j]=F_column[i][j]+g_column[i][k]*F_rowT[k][j];
			}
		}
	}
	for(i=0;i<(int)biHeight;i++)//转置M*N
	{
		for(j=0;j<(int)biWidth;j++)
		{
		    F_columnT[j][i]=F_column[i][j];
		}
	}
	for(y=0;y<(int)biHeight;y++)//改变像素值
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			m_pTransfered[cur]=F_columnT[x][y];
		}
	}
	UpdateAllViews(NULL);
}

void CWvltDoc::OnEdgeDetection()//边缘检测 
{
	// TODO: Add your command handler code here
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;
	int x,y,cur;
	unsigned char *old;//存储改变之前的值
	old=(unsigned char*)malloc(bmSize);
	unsigned char *Gx;
	Gx=(unsigned char*)malloc(bmSize);
	unsigned char *Gy;
	Gy=(unsigned char*)malloc(bmSize);
	unsigned char *G;
	G=(unsigned char*)malloc(bmSize);
	int cur00,cur01,cur02,cur10,cur12,cur20,cur21,cur22;
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			old[cur]=lpData[cur];
			old[cur+1]=lpData[cur+1];
			old[cur+2]=lpData[cur+2];
		}
	}
	for(y=0;y<(int)biHeight;y++)//3*3Box模板
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			G[cur]=(old[cur00]+old[cur01]+old[cur02]+
				old[cur10]+old[cur]+old[cur12]+
				old[cur20]+old[cur21]+old[cur22])/9;
		}
	}
	for(y=0;y<(int)biHeight;y++)//Sobel算子
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			Gx[cur]=G[cur00]*-1+G[cur01]*0+G[cur02]*1+
				G[cur10]*-2+G[cur]*0+G[cur12]*2+
				G[cur20]*-1+G[cur21]*0+G[cur22]*1;
			Gy[cur]=G[cur00]*-1+G[cur01]*-2+G[cur02]*-1+
				G[cur10]*0+G[cur]*0+G[cur12]*0+
				G[cur20]*1+G[cur21]*2+G[cur22]*1;
			m_pTransfered[cur]=abs(Gx[cur])+abs(Gy[cur]);
			if(m_pTransfered[cur]>80)//阈值分割
			{
				m_pTransfered[cur]=255;
				m_pTransfered[cur+1]=255;
				m_pTransfered[cur+2]=255;
			}
			else
			{
				m_pTransfered[cur]=0;
				m_pTransfered[cur+1]=0;
				m_pTransfered[cur+2]=0;
			}
		}
	}
	UpdateAllViews(NULL);
}

void CWvltDoc::OnEdgeExtraction()//轮廓提取 
{
	// TODO: Add your command handler code here
	LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)(m_pBitmap+14);
	LPBITMAPFILEHEADER lpBitmapFileHeader = (LPBITMAPFILEHEADER)m_pBitmap;
	unsigned char *lpData = m_pBitmap + lpBitmapFileHeader->bfOffBits;
	unsigned long biHeight = lpBitmapInfoHeader->biHeight;
	unsigned long biWidth = lpBitmapInfoHeader->biWidth;
	unsigned long biAlign = ( biWidth*3+3) /4 *4;
	unsigned long bmSize = biHeight * biAlign;
	if (m_pTransfered == NULL)
		m_pTransfered = (unsigned char*)malloc(bmSize);
	if (m_pTransfered == NULL)
		return ;
	int x,y,cur;
	char pixel1=0,pixel2=0;
	int T1=24,T2,num1=0,num2=0;
	unsigned char *old;//存储改变之前的值
	old=(unsigned char*)malloc(bmSize);
	unsigned char *Gx;
	Gx=(unsigned char*)malloc(bmSize);
	unsigned char *Gy;
	Gy=(unsigned char*)malloc(bmSize);
	unsigned char *G;
	G=(unsigned char*)malloc(bmSize);
	int cur00,cur01,cur02,cur10,cur12,cur20,cur21,cur22;
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			old[cur]=lpData[cur];
			old[cur+1]=lpData[cur+1];
			old[cur+2]=lpData[cur+2];
		}
	}
	for(y=0;y<(int)biHeight;y++)//3*3Box模板
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			G[cur]=(old[cur00]+old[cur01]+old[cur02]+
				old[cur10]+old[cur]+old[cur12]+
				old[cur20]+old[cur21]+old[cur22])/9;
		}
	}
	for(y=0;y<(int)biHeight;y++)//Sobel算子
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			Gx[cur]=G[cur00]*-1+G[cur01]*0+G[cur02]*1+
				G[cur10]*-2+G[cur]*0+G[cur12]*2+
				G[cur20]*-1+G[cur21]*0+G[cur22]*1;
			Gy[cur]=G[cur00]*-1+G[cur01]*-2+G[cur02]*-1+
				G[cur10]*0+G[cur]*0+G[cur12]*0+
				G[cur20]*1+G[cur21]*2+G[cur22]*1;
			old[cur]=abs(Gx[cur])+abs(Gy[cur]);
		}
	}
	/*while(true)//迭代阈值分割
	{
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			if(old[cur]>T1)
			{
				pixel1=pixel1+old[cur];
				num1++;
			}
			else
			{
				pixel2=pixel2+old[cur];
				num2++;
			}
		}
	}
	T2=(pixel1/num1+pixel2/num2)/2;
	if(abs(T2-T1)<=0)
		break;
	else
	{
		T1=T2;
		pixel1=0;
		pixel2=0;
		num1=0;
		num2=0;
	}
	}*/
	for(y=0;y<(int)biHeight;y++)
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			if(old[cur]>30)
			//if(old[cur]>T2)
			{
				old[cur]=255;
				old[cur+1]=255;
				old[cur+2]=255;
			}
			else
			{
				old[cur]=0;
				old[cur+1]=0;
				old[cur+2]=0;
			}
		}
	}
	for(y=0;y<(int)biHeight;y++)//轮廓提取
	{
		for(x=0;x<(int)biWidth;x++)
		{
			cur=y*biAlign+3*x;
			cur00=(y-1)*biAlign+3*(x-1);
			cur01=(y-1)*biAlign+3*x;
			cur02=(y-1)*biAlign+3*(x+1);
			cur10=y*biAlign+3*(x-1);
			cur12=y*biAlign+3*(x+1);
			cur20=(y+1)*biAlign+3*(x-1);
			cur21=(y+1)*biAlign+3*x;
			cur22=(y+1)*biAlign+3*(x+1);
			if(old[cur00]==0&&old[cur01]==0&&old[cur02]==0&&old[cur10]==0&&old[cur]==0
				&&old[cur12]==0&&old[cur20]==0&&old[cur21]==0&&old[cur22]==0)
			{
				old[cur]=255;
				old[cur+1]=255;
				old[cur+2]=255;
			}
			m_pTransfered[cur]=old[cur];
			m_pTransfered[cur+1]=old[cur+1];
			m_pTransfered[cur+2]=old[cur+2];
		}
	}
	UpdateAllViews(NULL);
}
