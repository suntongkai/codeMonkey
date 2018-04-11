// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define Round(d) int(floor(d+0.5))//��������궨��
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

void CTestView::ReadPoint()//���
{
	P[0].x=50;  P[0].y=100;
	P[1].x=-150;P[1].y=300;
	P[2].x=-250;P[2].y=50;
	P[3].x=-150;P[3].y=-250;
	P[4].x=0;   P[4].y=-50;
	P[5].x=100; P[5].y=-250;
	P[6].x=300; P[6].y=150;
}

void CTestView::DrawGraph()//����ͼ��
{
	GetClientRect(&rect);                               //��ÿͻ����Ĵ�С
	CDC *pDC=GetDC();                                   //�����豸������ָ��              
	pDC->SetMapMode(MM_ANISOTROPIC);                    //�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());      //���ô��ڱ���
	pDC->SetViewportExt(rect.Width(),-rect.Height());   //����������������x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//���ÿͻ�������Ϊ����ϵԭ��
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);  //������ͻ����غ�
	if(!bFill)
		DrawPolygon(pDC);//���ƶ����
	else
		FillPolygon(pDC);//�������
	ReleaseDC(pDC);//�ͷ�DC
}

void CTestView::DrawPolygon(CDC *pDC)//���ƶ���α߽�
{
	CLine *line=new CLine;
	CP2 t;
	for(int i=0;i<7;i++)//���ƶ����
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
	line->LineTo(pDC,t);//�պ϶����
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
	int x1,x2;//��䷶Χ
	COLORREF color;
	int front=1;//����ɨ��ʱ���ǰһ�������Ƿ�Ϊ�߽�
	while(true)
	{
	    p=popstack(&s);
		while(p.x-i>-250)//����
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
		while(p.x+j<300)//���һ�
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
				front=0;//ǰһ��Ϊ�ڲ���
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
void CTestView::FillPolygon(CDC *pDC)//�������
{
	//��������㷨
	//01:y=-x+150
	//12:y=5/2*x+675
	//23:y=-3*x-700;
	//34:y=4/3*x-50
	//45:y=-2*x-50
	//56:y=2*x-450
	//60:y=1/5*x+90
	Stack s;
	initstack(&s);
	int isinside=0;//����Ƿ����ڲ���
	bool isup=1;//����Ƿ�����ɨ��
	if(Seed.y>=300||Seed.y<=-250||Seed.x>=300||Seed.x<=-250)
	{
		MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ");
		isinside=0;
	}
	if(Seed.y<300&&Seed.y>-250&&Seed.x<300&&Seed.x>-250)
	{
		if(2*5/2*Seed.x+2*675-2*Seed.y<=0)
		{
			MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ1");
			isinside=0;
		}
		else if(-Seed.x+150-Seed.y<0&&5*1/5*Seed.x+5*90-5*Seed.y<0)
		{
			MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ2");
			isinside=0;
		}
		else if(-3*Seed.x-700-Seed.y>=0)
		{
			MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ3");
			isinside=0;
		}
		else if(3*4/3*Seed.x-3*50-3*Seed.y>0&&-2*Seed.x-50-Seed.y>0)
		{
			MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ4");
			isinside=0;
		}
		else if(2*Seed.x-450-Seed.y>=0)
		{
			MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ5");
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
	MessageBox("������","��ʾ");
	}
}

void CTestView::OnDrawpic() 
{
	// TODO: Add your command handler code here
	CColorDialog ccd(SeedClr,CC_SOLIDCOLOR);
	if(IDOK==ccd.DoModal())//������ɫ�Ի���ѡȡ���ɫ
		SeedClr=ccd.GetColor();	
	else
		return;	
	if(IDOK==MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ",MB_OKCANCEL))
	    bFill=TRUE;
	else
		return;	
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(TRUE==bFill)
	{
		Seed=CP2(point.x-rect.Width()/2,rect.Height()/2-point.y);//ѡ������λ��
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


