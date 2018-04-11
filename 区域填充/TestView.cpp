// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define Round(d) int(floor(d+0.5))//四舍五入宏定义
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(IDM_DRAWPIC, OnDrawpic)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	
	DrawGraph();
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::ReadPoint()//点表
{
	P[0].x=50;  P[0].y=100;
	P[1].x=-150;P[1].y=300;
	P[2].x=-250;P[2].y=50;
	P[3].x=-150;P[3].y=-250;
	P[4].x=0;   P[4].y=-50;
	P[5].x=100; P[5].y=-250;
	P[6].x=300; P[6].y=150;
}

void CTestView::DrawGraph()//绘制图形
{
	GetClientRect(&rect);                               //获得客户区的大小
	CDC *pDC=GetDC();                                   //定义设备上下文指针              
	pDC->SetMapMode(MM_ANISOTROPIC);                    //自定义坐标系
	pDC->SetWindowExt(rect.Width(),rect.Height());      //设置窗口比例
	pDC->SetViewportExt(rect.Width(),-rect.Height());   //设置视区比例，且x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//设置客户区中心为坐标系原点
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);  //矩形与客户区重合
	if(!bFill)
		DrawPolygon(pDC);//绘制多边形
	else
		FillPolygon(pDC);//填充多边形
	ReleaseDC(pDC);//释放DC
}

void CTestView::DrawPolygon(CDC *pDC)//绘制多边形边界
{
	CLine *line=new CLine;
	CP2 t;
	for(int i=0;i<7;i++)//绘制多边形
	{
		if(i==0)
		{
			line->MoveTo(pDC,P[i]);
			t=P[i];
		}
		else
		{
			line->LineTo(pDC,P[i]);
		}		
	}
	line->LineTo(pDC,t);//闭合多边形
	delete line;
}
typedef struct Stack
{
    CP2 p[800];
	int top;
}Stack;
void initstack(Stack *s)
{
	s->top=-1;
}
void pushstack(Stack *s,CP2 seed)
{
	if(s->top<800-1)
	{
		s->top++;
		s->p[s->top].x=seed.x;
		s->p[s->top].y=seed.y;
	}
}
CP2 popstack(Stack *s)
{
	CP2 p;
	if(s->top!=-1)
	{
		p.x=s->p[s->top].x;
		p.y=s->p[s->top].y;
		s->top--;
	}
	return p;
}
void fill(Stack s,CDC *pDC,COLORREF SeedClr,bool isup)
{
	CP2 p,pp;
	int i=0,j=1;
	int x1,x2;//填充范围
	COLORREF color;
	int front=1;//上下扫描时标记前一个像素是否为边界
	while(true)
	{
	    p=popstack(&s);
		while(p.x-i>-250)//向左画
		{
		    color=pDC->GetPixel((int)p.x-i,(int)p.y);
		    if(color==RGB(0,0,0))
			{
				x1=p.x-i+1;
			    break;
			}
			pDC->SetPixel((int)p.x-i,(int)p.y,SeedClr);
			i++;
		}
		while(p.x+j<300)//向右画
		{
		    color=pDC->GetPixel((int)p.x+j,(int)p.y);
		    if(color==RGB(0,0,0))
			{
				x2=p.x+j-1;
			    break;
			}
			pDC->SetPixel((int)p.x+j,(int)p.y,SeedClr);
			j++;
		}
		pp.x=x1;
		if(isup==1)
			pp.y=p.y+1;
		else
		    pp.y=p.y-1;
		while(pp.x<=x2)
		{
            color=pDC->GetPixel((int)pp.x,(int)pp.y);
			if(color!=RGB(0,0,0)&&front==1)
			{
				pushstack(&s,pp);
				front=0;//前一个为内部点
			}
			if(color==RGB(0,0,0))
				front=1;
			pp.x++;
		}
		i=0;
		j=1;
		front=1;
	    if(s.top==-1)
			break;
	}
}
void CTestView::FillPolygon(CDC *pDC)//填充多边形
{
	//种子填充算法
	//01:y=-x+150
	//12:y=5/2*x+675
	//23:y=-3*x-700;
	//34:y=4/3*x-50
	//45:y=-2*x-50
	//56:y=2*x-450
	//60:y=1/5*x+90
	Stack s;
	initstack(&s);
	int isinside=0;//标记是否是内部点
	bool isup=1;//标记是否向上扫描
	if(Seed.y>=300||Seed.y<=-250||Seed.x>=300||Seed.x<=-250)
	{
		MessageBox("请在区域内部选取种子点","提示");
		isinside=0;
	}
	if(Seed.y<300&&Seed.y>-250&&Seed.x<300&&Seed.x>-250)
	{
		if(2*5/2*Seed.x+2*675-2*Seed.y<=0)
		{
			MessageBox("请在区域内部选取种子点","提示1");
			isinside=0;
		}
		else if(-Seed.x+150-Seed.y<0&&5*1/5*Seed.x+5*90-5*Seed.y<0)
		{
			MessageBox("请在区域内部选取种子点","提示2");
			isinside=0;
		}
		else if(-3*Seed.x-700-Seed.y>=0)
		{
			MessageBox("请在区域内部选取种子点","提示3");
			isinside=0;
		}
		else if(3*4/3*Seed.x-3*50-3*Seed.y>0&&-2*Seed.x-50-Seed.y>0)
		{
			MessageBox("请在区域内部选取种子点","提示4");
			isinside=0;
		}
		else if(2*Seed.x-450-Seed.y>=0)
		{
			MessageBox("请在区域内部选取种子点","提示5");
			isinside=0;
		}
		else
			isinside=1;
	}
	if(isinside==1)
	{
	pushstack(&s,Seed);
	fill(s,pDC,SeedClr,1);
	fill(s,pDC,SeedClr,0);
	MessageBox("填充完毕","提示");
	}
}

void CTestView::OnDrawpic() 
{
	// TODO: Add your command handler code here
	CColorDialog ccd(SeedClr,CC_SOLIDCOLOR);
	if(IDOK==ccd.DoModal())//调用颜色对话框选取填充色
		SeedClr=ccd.GetColor();	
	else
		return;	
	if(IDOK==MessageBox("请在区域内部选取种子点","提示",MB_OKCANCEL))
	    bFill=TRUE;
	else
		return;	
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(TRUE==bFill)
	{
		Seed=CP2(point.x-rect.Width()/2,rect.Height()/2-point.y);//选择种子位置
		Invalidate(FALSE);
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	bFill=FALSE;
	SeedClr=RGB(0,0,255);
	ReadPoint();
}


