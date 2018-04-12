#include<iostream>
#include<cstring>
#include<malloc.h>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<ctime>
using namespace std;
int space=0;//��¼�����SQL���Ե����һ���ո�
char name[10];//����
int column=0;//����
struct Node//һ���ṹ�����洢һ����¼
	{
		char **data;
		struct Node* next;
	};
void Save(char *filename,Node *p,int column,char **attribute)//���浽�ı��ĵ�
{
	int i=0;
	ofstream outfile(filename);
    for(i=0;i<16*(column+1);i++)
	{outfile<<'-';}
	outfile<<endl;
	for(i=0;i<column+1;i++)
	{outfile<<setfill(' ')<<setw(15)<<attribute[i]<<'|';}
	outfile<<endl;
	for(i=0;i<16*(column+1);i++)
	{outfile<<'-';}
	outfile<<endl;
    while(p->next)
    {for(i=0;i<column+1;i++)
    {outfile<<setfill(' ')<<setw(15)<<p->next->data[i];
    outfile<<'|';
    }
    outfile<<endl;
    p=p->next;
	}
	for(i=0;i<16*(column+1);i++)
	{outfile<<'-';}
    outfile.close();
    cout<<"������"<<filename<<"��"<<endl;
}
bool findwhere(char *input)//ʶ���Ƿ���WHERE
{
	char func[7];
	int i=0,j=0,record=0;
	for(i=0;input[i]!=';';i++)
	{}
    record=i;//�ֺ�λ��
	for(i=record;input[i]!=' ';i--)
	{}
	record=i;//�ո�λ��
	space=i;
	for(j=0;j<5;j++)
	{func[j]=input[record-5];
	record++;
	}
	func[j]='\0';
	if(strcmp(func,"WHERE")==0)
	{return 1;}
	return 0;
}
int selfunc(char *input,bool flag)//ʶ����
{
	int i=0;
    char function[7];//������
    int record;//��¼�ַ�λ��
    for(i=0;input[i]!=' ';i++)
	{function[i]=input[i];}
	record=i;//�ո�λ��
	function[i]='\0';
	if(strcmp(function,"CREATE")==0)
	{for(i=record+1;input[i]!=' ';i++)
	{function[i-record-1]=input[i];}
	function[i-record-1]='\0';
	if(strcmp(function,"TABLE")==0)
	{return 1;}
	if(strcmp(function,"INDEX")==0)
	{if(flag==0)
	{cout<<"��δ����!"<<endl;
	return -1;}
	return 6;
	}
	else
	{cout<<"�������!"<<endl;
	return -1;
	}
	}
    else if(strcmp(function,"SELECT")==0)
	{if(flag==0)
	{cout<<"��δ����!"<<endl;
	return -1;}
	return 2;
	}
	else if(strcmp(function,"INSERT")==0)
	{if(flag==0)
	{cout<<"��δ����!"<<endl;
	return -1;}
	return 3;}
	else if(strcmp(function,"DELETE")==0)
	{if(flag==0)
	{cout<<"��δ����!"<<endl;
	return -1;}
	return 4;}
	else if(strcmp(function,"UPDATE")==0)
	{if(flag==0)
	{cout<<"��δ����!"<<endl;
	return -1;}
	return 5;}
	else
	{cout<<"�������!"<<endl;
	return -1;
	}
}
void showall(Node *p,int column)//��ʾ��������
{
	int i=0;
    while(p->next)
	{for(i=0;i<column+1;i++)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[i];
    cout<<'|';
	}
    cout<<endl;
    p=p->next;
	}
}
void drawtable(int column)//�������
{
	int i=0;
    for(i=0;i<16*(column+1);i++)
	{cout<<'-';}
    cout<<endl;
}
void showone(Node *p,int Record)//��������ѯ��ʾһ��
{
	while(p->next)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[Record];
    cout<<'|'<<endl;
    p=p->next;
	}
}
void showone_many(Node *p,int *selnum,int num)//���������в�ѯ
{
	int l=0;
	while(p->next)
	{for(l=0;l<num+1;l++)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[selnum[l]];
    cout<<'|';}
    cout<<endl;
    p=p->next;
	}
}
void insertone(Node *p,int Record,char *findvalue)//����һ����ֵ
{
	Node *s;
	int i;
	while(p->next)
	{p=p->next;}
    s=(Node*)malloc(sizeof(Node));
	s->data=new char*[column+1];
	for(i=0;i<column+1;i++)
	{s->data[i]=new char[20];}//һ���м�¼��Ӧһ���ַ�����
	for(i=0;i<column+1;i++)
	{s->data[i][0]='\0';}
	strcpy(s->data[Record],findvalue);
	p->next=s;
	s->next=NULL;
	cout<<"����޸�!"<<endl;
}
void insertall(Node *p,int *innum,char **invalue,int num)//��������ֵ
{
	Node *s;
	int i;
	while(p->next)
	{p=p->next;}
    s=(Node*)malloc(sizeof(Node));
	s->data=new char*[column+1];
	for(i=0;i<column+1;i++)
	{s->data[i]=new char[20];}//һ���м�¼��Ӧһ���ַ�����
	for(i=0;i<column+1;i++)
	{s->data[i][0]='\0';}
	for(i=0;i<num+1;i++)
	{strcpy(s->data[innum[i]],invalue[i]);}
	p->next=s;
	s->next=NULL;
	cout<<"����޸�!"<<endl;
}
void showone_where(Node *p,int Record,char *findvalue,int Record2)//������ѯ��ʾһ��
{
	while(p->next)
	{if(strcmp(findvalue,p->next->data[Record2])==0)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[Record];
    cout<<'|'<<endl;
	}
    p=p->next;
	}
}
void showone_wheremany(Node *p,int *selnum,char *findvalue,int Record2,int num)//������ѯ���в�ѯ
{
	int l=0;
    while(p->next)
	{if(strcmp(findvalue,p->next->data[Record2])==0)
	{for(l=0;l<num+1;l++)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[selnum[l]];
    cout<<'|';
	}
	cout<<endl;
	}
    p=p->next;
	}
}
void Delete(Node *p,int Record,char *findvalue)//ɾ��
{ 
	Node *s;
	while(p->next)
	{if(strcmp(findvalue,p->next->data[Record])==0)
    {s=p->next;
	p->next=s->next;
	free(s);}
	p=p->next;
	}
}
void Update(Node *p,int Record,char *findvalue)//�޸�
	   {
		   while(p->next)
		   {
		   strcpy(p->next->data[Record],findvalue);
		   p=p->next;
		   }
	   }
void seltime(double start,double finish)//�����ѯʱ��
{
	double time;//��ѯʱ��
	time=(double)(finish-start)/(double)CLK_TCK;
	cout<<"���β�ѯ��ʱ"<<time<<"��"<<endl;
}
int main()
{
	char input[100];//����
	char Attribute[20];//���ڲ�������
    char **attribute;//����
	int i=0,j=0,k=0,l=0;
	int record=0;//��¼�ַ�λ��
	int Record=-1;//��¼�����
	int num=0;//���Ÿ���
	bool flag=0;//����Ƿ񽨱�
	int *selnum;//��ѯ������
	char end=0;//����������
	Node *p,*s;//����ͷ�ڵ�
	char Name[10];//ʶ�����
	char findattri[20];//��¼��ѯ����������
	char findvalue[20];//��¼��ѯ���������Ե�ֵ
	int Record2=-1;//��¼�����е����
	clock_t start,finish;//�����ѯʱ��
	char End=0;//��������������
	int *innum;//��¼���������
	char **invalue;
	cout<<"��ӭʹ��!"<<endl<<endl;
	cout<<"������:"<<endl;
	cout<<"��ͯ��,����,����,�ܼ��"<<endl<<endl;
	cout<<"������SQL����:"<<endl;
    while(true)
	{cin.getline(input,250,'\n');//����SQL����
	if(selfunc(input,flag)==-1)//�쳣
	{return 0;}
	if(selfunc(input,flag)==1)//ѡ�񽨱���
	{
		cout<<"ѡ�񽨱���"<<endl;
		for(i=13;input[i]!='(';i++)//ʶ�����
	{name[i-13]=input[i];}
	name[i-13]='\0';
	record=i;//������λ��
	if(strcmp(name,"")==0)
	{cout<<"δ�������!"<<endl;
	return 0;
	}
	else
	{cout<<"����Ϊ:"<<name<<endl;}
		for(i=0;input[i]!='(';i++)
	{}
    record=i;//������λ��
	num=0;
	for(i=record+1;input[i]!=')';i++)//�����Ÿ���=����-1
	{if(input[i]==',')
	{num++;}
	}
	column=num;
	attribute=new char*[column+1];
	for(i=0;i<column+1;i++)
	{attribute[i]=new char[20];}
	if(num==0)//ֻ��һ����
	{j=0;
	l=0;
	for(i=record+1;input[i]!=' ';i++)
	{attribute[j][l]=input[i];
	l++;
	}
	attribute[j][l]='\0';
	}
	else
	{while(num>0)//�ж����
	{l=0;
	for(i=record+1;input[i]!=' ';i++)
	{attribute[j][l]=input[i];
	l++;
	}
	attribute[j][l]='\0';
	j++;
	l=0;
	for(i;input[i]!=',';i++)
	{}
	num--;
	record=i;//����λ��
	}
	for(i=record+1;input[i]!=' ';i++)//���һ����
	{attribute[j][l]=input[i];
	l++;
	}
	attribute[j][l]='\0';
	}
	cout<<"��ĸ�����Ϊ:"<<endl;
	drawtable(column);
	for(i=0;i<column+1;i++)
	{cout<<setfill(' ')<<setw(15)<<attribute[i]<<'|';}
	cout<<endl;
	drawtable(column);
	cout<<endl;
	flag=1;//����ɽ���
	}
	if(selfunc(input,flag)==6)//ѡ������������
	{cout<<"�밴����������:"<<endl;
	for(i=16;input[i]!=';';i++)
	    {Name[i-16]=input[i];}
	    Name[i-16]='\0';
	    if(strcmp(Name,name)!=0)
	    {cout<<"��������ȷ!"<<endl;
	    return 0;
	    }
	p=(Node*)malloc(sizeof(Node));
	p->next=NULL;
	while(end!='\r')
	{s=(Node*)malloc(sizeof(Node));
	s->data=new char*[column+1];
	for(i=0;i<column+1;i++)
	{s->data[i]=new char[20];}//һ���м�¼��Ӧһ���ַ�����
	for(i=0;i<column+1;i++)//�����������
	{cin.getline(s->data[i],20,'\n');}
	cout<<"��������һ������,�򰴻س�����������:"<<endl;
	s->next=p->next;
	p->next=s;
	end=getch();//�س�����������
	}
	cout<<"����ɽ���"<<endl;
	cout<<"������������:"<<endl;
	drawtable(column);
	for(i=0;i<column+1;i++)
	{cout<<setfill(' ')<<setw(15)<<attribute[i];
	cout<<'|';
	}
	cout<<endl;
	drawtable(column);
	showall(p,column);//��ʾ��������
	drawtable(column);
	Save("TextFile.txt",p,column,attribute);
	cout<<endl;
	}
	if(selfunc(input,flag)==2)//ѡ���ѯ����
	{
		cout<<"ѡ���ѯ����"<<endl;
		start=clock();
		for(i=0;input[i]!=' ';i++)
		{}
	record=i;//�ո�λ��
		if(findwhere(input)==0)//�жϱ����Ƿ���ȷ//û��WHERE
	{for(i=space+1;input[i]!=';';i++)
	{Name[i-space-1]=input[i];}
	Name[i-space-1]='\0';
	if(strcmp(Name,name)!=0)
	{cout<<"��������ȷ!"<<endl;
	return 0;
	}
	}
	else//��WHERE
	{for(i=space-1;input[i]!=' ';i--)
	{}
	j=i;//������Ŀո�
	for(i=j-1;input[i]!=' ';i--)
	{}
	j=i;//FROM��Ŀո�
	for(i=j+1;input[i]!=' ';i++)
	{Name[i-j-1]=input[i];}
	Name[i-j-1]='\0';
	if(strcmp(Name,name)!=0)
	{cout<<"��������ȷ!"<<endl;
	return 0;
	}
	}
	num=0;
	for(i=record+1;input[i]!='\0';i++)//Ҫ��ѯ������-1
	{if(input[i]==',')
	{num++;}
	}
	k=num;
	Record=-1;
	if(findwhere(input)==0)//û��WHERE
	{if(k==0)//ֻ��ѯһ����
	{for(i=record+1;input[i]!=' ';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;}
	drawtable(num);
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	drawtable(num);
	showone(p,Record);//�����ѯ���
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	else//��ѯ�����
	{drawtable(num);
	selnum=new int[num+1];
	l=0;
	while(k>0)
	{for(i=record+1;input[i]!=',';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	record=i;//���ŵ�λ��
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;
	}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|';
	selnum[l]=Record;
	l++;
	k--;
	Record=-1;
	}
	for(i=record+1;input[i]!=' ';i++)//ʶ����������һ��
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	selnum[l]=Record;
	drawtable(num);
	showone_many(p,selnum,num);//�����ѯ���
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	}
	Record=-1;
	if(findwhere(input)==1)//��WHERE
	{if(k==0)//ֻ��ѯһ����
	{for(i=record+1;input[i]!=' ';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(i=0;input[i]!=';';i++)
	{}
	j=i;//�ֺ�λ��
	for(i=j;input[i]!='=';i--)
	{}
	j=i;//���ں�λ��
	for(i=j+1;input[i]!=';';i++)
	{findvalue[i-j-1]=input[i];}
	findvalue[i-j-1]='\0';
	for(i=space+1;input[i]!='=';i++)
	{findattri[i-space-1]=input[i];}
	findattri[i-space-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	for(j=0;j<column+1;j++)
	{if(strcmp(findattri,attribute[j])==0)
	{Record2=j;}
	}
	if(Record==-1||Record2==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;}
	drawtable(num);
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	drawtable(num);
	showone_where(p,Record,findvalue,Record2);
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	else//��ѯ�����
	{drawtable(num);
	selnum=new int[num+1];
	l=0;
	while(k>0)
	{for(i=record+1;input[i]!=',';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	record=i;//���ŵ�λ��
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;
	}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|';
	selnum[l]=Record;
	l++;
	k--;
	Record=-1;
	}
	for(i=record+1;input[i]!=' ';i++)//ʶ����������һ��
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	selnum[l]=Record;
	for(i=0;input[i]!=';';i++)
	{}
	j=i;//�ֺ�λ��
	for(i=j;input[i]!='=';i--)
	{}
	j=i;//���ں�λ��
	for(i=j+1;input[i]!=';';i++)
	{findvalue[i-j-1]=input[i];}
	findvalue[i-j-1]='\0';
	for(i=space+1;input[i]!='=';i++)
	{findattri[i-space-1]=input[i];}
	findattri[i-space-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(findattri,attribute[j])==0)
	{Record2=j;}
	}
	if(Record2==-1)
	{cout<<"��ѯ���в�����!"<<endl;
	return 0;}
	drawtable(num);
	showone_wheremany(p,selnum,findvalue,Record2,num);
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	}
	}
	if(selfunc(input,flag)==3)//ѡ����빦��
	{
		cout<<"ѡ����빦��"<<endl;
		for(i=12;input[i]!='(';i++)
	    {Name[i-12]=input[i];}
	    Name[i-12]='\0';
		record=i;//�����ŵ�λ��
	    if(strcmp(Name,name)!=0)
	    {cout<<"��������ȷ!"<<endl;
	    return 0;
	    }
        num=0;
		Record=-1;
	    for(i=0;input[i]!=')';i++)//Ҫ���������-1
	    {if(input[i]==',')
	    {num++;}
	    }
	    k=num;
		if(k==0)//ֻ����һ��
		{for(i=record+1;input[i]!=')';i++)
	    {findattri[i-record-1]=input[i];}
	    findattri[i-record-1]='\0';
        for(i=0;input[i]!=')';i++)
		{}
		record=i;//��һ�������ŵ�λ��
		for(i=record+1;input[i]!='(';i++)
		{}
		record=i;//�ڶ��������ŵ�λ��
		for(i=record+1;input[i]!=')';i++)
		{findvalue[i-record-1]=input[i];}
		findvalue[i-record-1]='\0';
	    for(j=0;j<column+1;j++)
	    {if(strcmp(findattri,attribute[j])==0)
	    {Record=j;}
	    }
	    if(Record==-1)
	    {cout<<"��ѯ���в�����!"<<endl;
	    return 0;}
		insertone(p,Record,findvalue);
		Save("TextFile.txt",p,column,attribute);
		drawtable(column);
		for(i=0;i<column+1;i++)
		{cout<<setfill(' ')<<setw(15)<<attribute[i];
	    cout<<'|';
		}
	    cout<<endl;
		drawtable(column);
		showall(p,column);
		drawtable(column);
	    }
		else//�������
		{l=0;
		innum=new int[num+1];
	    while(k>0)
	    {for(i=record+1;input[i]!=',';i++)
	    {findattri[i-record-1]=input[i];}
	    findattri[i-record-1]='\0';
	    record=i;//���ŵ�λ��
	    for(j=0;j<column+1;j++)
	    {if(strcmp(findattri,attribute[j])==0)
	    {Record=j;}
	    }
	    if(Record==-1)
	    {cout<<"��ѯ���в�����!"<<endl;
	    return 0;
	    }
	    innum[l]=Record;
	    l++;
	    k--;
	    Record=-1;
		}
	    for(i=record+1;input[i]!=')';i++)//ʶ����������һ��
		{Attribute[i-record-1]=input[i];}
	    Attribute[i-record-1]='\0';
	    for(j=0;j<column+1;j++)
		{if(strcmp(Attribute,attribute[j])==0)
		{Record=j;}
		}
	    if(Record==-1)
		{cout<<"��ѯ���в�����!"<<endl;
	    return 0;}
	    innum[l]=Record;
	    k=num;
	    invalue=new char*[num+1];
	    for(i=0;i<num+1;i++)
		{invalue[i]=new char[10];}
        for(i=0;input[i]!=')';i++)
		{}
		record=i;//��һ�������ŵ�λ��
		for(i=record+1;input[i]!='(';i++)
		{}
		record=i;//�ڶ��������ŵ�λ��
		l=0;
		while(k>0)
	    {for(i=record+1;input[i]!=',';i++)
	    {invalue[l][i-record-1]=input[i];}
	    invalue[l][i-record-1]='\0';
	    record=i;//���ŵ�λ��
	    l++;
	    k--;
		}
		for(i=record+1;input[i]!=')';i++)//ʶ����������һ��
		{invalue[l][i-record-1]=input[i];}
		invalue[l][i-record-1]='\0';
        insertall(p,innum,invalue,num);
		Save("TextFile.txt",p,column,attribute);
		drawtable(column);
		for(i=0;i<column+1;i++)
		{cout<<setfill(' ')<<setw(15)<<attribute[i];
	    cout<<'|';
		}
	    cout<<endl;
		drawtable(column);
		showall(p,column);
		drawtable(column);
		}
	}
	if(selfunc(input,flag)==4)//ѡ��ɾ������
	{cout<<"ѡ��ɾ�����ܣ�"<<endl;
	for(i=12;input[i]!=' ';i++)
	{Name[i-12]=input[i];}
	Name[i-12]='\0';
	if(strcmp(Name,name)!=0)
	{cout<<"��������ȷ��"<<endl;
	return 0;
	}
	Record=-1;
		for(i=0;input[i]!=';';i++)
		{}
		j=i;//�ֺ�λ��
		for(i=j;input[i]!=' ';i--)
		{}
		j=i;//�ո�λ��
		for(i=j+1;input[i]!='=';i++)
		{findattri[i-j-1]=input[i];}
		findattri[i-j-1]='\0';
		j=i;//�Ⱥ�λ��
		for(i=j+1;input[i]!=';';i++)
		{findvalue[i-j-1]=input[i];}
		findvalue[i-j-1]='\0';
		for(j=0;j<column+1;j++)
		{if(strcmp(findattri,attribute[j])==0)
		{Record=j;}
		}
		if(Record==-1)
		{cout<<"ɾ�����в�����!"<<endl;
	    return 0;}
		Delete(p,Record,findvalue);
		Save("TextFile.txt",p,column,attribute);
drawtable(column);
for(i=0;i<column+1;i++)
		{cout<<setfill(' ')<<setw(15)<<attribute[i];
	    cout<<'|';
		}
	    cout<<endl;
		drawtable(column);
		showall(p,column);
		drawtable(column);
}
	if(selfunc(input,flag)==5)//ѡ���޸Ĺ���
{
cout<<"ѡ���޸Ĺ���"<<endl;
for(i=7;input[i]!=' ';i++)
    {Name[i-7]=input[i];}
    Name[i-7]='\0';
record=i;//�ո��λ��
    if(strcmp(Name,name)!=0)
    {cout<<"��������ȷ!"<<endl;
    return 0;
    }
	Record=-1;
   for(i=0;input[i]!=';';i++)
		{}
		j=i;//�ֺ�λ��
		for(i=j;input[i]!=' ';i--)
		{}
		j=i;//�ո�λ��
		for(i=j+1;input[i]!='=';i++)
	{findattri[i-j-1]=input[i];}
	findattri[i-j-1]='\0';
	j=i;//�Ⱥ�λ��
		for(i=j+1;input[i]!=';';i++)
		{findvalue[i-j-1]=input[i];}
		findvalue[i-j-1]='\0';	   
	for(j=0;j<column+1;j++)
	{if(strcmp(findattri,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"��ѯ���в�����!"<<endl;
return 0;
}
	Update(p,Record,findvalue);
	Save("TextFile.txt",p,column,attribute);
drawtable(column);
	for(i=0;i<column+1;i++)
		{cout<<setfill(' ')<<setw(15)<<attribute[i];
	    cout<<'|';
		}
	    cout<<endl;
		drawtable(column);
		showall(p,column);
		drawtable(column);
	   }
	cout<<"��������SQL���Ի�ESC�˳�����"<<endl;
	End=getch();//��ESC����������
    if(End==27)
	{return 0;}
	}
	return 0;
}