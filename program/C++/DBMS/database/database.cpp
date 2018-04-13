#include<iostream>
#include<cstring>
#include<malloc.h>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<ctime>
using namespace std;
int space=0;//记录输入的SQL语言的最后一个空格
char name[10];//表名
int column=0;//列数
struct Node//一个结构体对象存储一条记录
	{
		char **data;
		struct Node* next;
	};
void Save(char *filename,Node *p,int column,char **attribute)//保存到文本文档
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
    cout<<"表保存在"<<filename<<"中"<<endl;
}
bool findwhere(char *input)//识别是否有WHERE
{
	char func[7];
	int i=0,j=0,record=0;
	for(i=0;input[i]!=';';i++)
	{}
    record=i;//分号位置
	for(i=record;input[i]!=' ';i--)
	{}
	record=i;//空格位置
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
int selfunc(char *input,bool flag)//识别功能
{
	int i=0;
    char function[7];//功能名
    int record;//记录字符位置
    for(i=0;input[i]!=' ';i++)
	{function[i]=input[i];}
	record=i;//空格位置
	function[i]='\0';
	if(strcmp(function,"CREATE")==0)
	{for(i=record+1;input[i]!=' ';i++)
	{function[i-record-1]=input[i];}
	function[i-record-1]='\0';
	if(strcmp(function,"TABLE")==0)
	{return 1;}
	if(strcmp(function,"INDEX")==0)
	{if(flag==0)
	{cout<<"还未建表!"<<endl;
	return -1;}
	return 6;
	}
	else
	{cout<<"输入错误!"<<endl;
	return -1;
	}
	}
    else if(strcmp(function,"SELECT")==0)
	{if(flag==0)
	{cout<<"还未建表!"<<endl;
	return -1;}
	return 2;
	}
	else if(strcmp(function,"INSERT")==0)
	{if(flag==0)
	{cout<<"还未建表!"<<endl;
	return -1;}
	return 3;}
	else if(strcmp(function,"DELETE")==0)
	{if(flag==0)
	{cout<<"还未建表!"<<endl;
	return -1;}
	return 4;}
	else if(strcmp(function,"UPDATE")==0)
	{if(flag==0)
	{cout<<"还未建表!"<<endl;
	return -1;}
	return 5;}
	else
	{cout<<"输入错误!"<<endl;
	return -1;
	}
}
void showall(Node *p,int column)//显示所有数据
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
void drawtable(int column)//画表格线
{
	int i=0;
    for(i=0;i<16*(column+1);i++)
	{cout<<'-';}
    cout<<endl;
}
void showone(Node *p,int Record)//无条件查询显示一列
{
	while(p->next)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[Record];
    cout<<'|'<<endl;
    p=p->next;
	}
}
void showone_many(Node *p,int *selnum,int num)//无条件多列查询
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
void insertone(Node *p,int Record,char *findvalue)//插入一个列值
{
	Node *s;
	int i;
	while(p->next)
	{p=p->next;}
    s=(Node*)malloc(sizeof(Node));
	s->data=new char*[column+1];
	for(i=0;i<column+1;i++)
	{s->data[i]=new char[20];}//一个行记录对应一个字符数组
	for(i=0;i<column+1;i++)
	{s->data[i][0]='\0';}
	strcpy(s->data[Record],findvalue);
	p->next=s;
	s->next=NULL;
	cout<<"完成修改!"<<endl;
}
void insertall(Node *p,int *innum,char **invalue,int num)//插入多个列值
{
	Node *s;
	int i;
	while(p->next)
	{p=p->next;}
    s=(Node*)malloc(sizeof(Node));
	s->data=new char*[column+1];
	for(i=0;i<column+1;i++)
	{s->data[i]=new char[20];}//一个行记录对应一个字符数组
	for(i=0;i<column+1;i++)
	{s->data[i][0]='\0';}
	for(i=0;i<num+1;i++)
	{strcpy(s->data[innum[i]],invalue[i]);}
	p->next=s;
	s->next=NULL;
	cout<<"完成修改!"<<endl;
}
void showone_where(Node *p,int Record,char *findvalue,int Record2)//条件查询显示一列
{
	while(p->next)
	{if(strcmp(findvalue,p->next->data[Record2])==0)
	{cout<<setfill(' ')<<setw(15)<<p->next->data[Record];
    cout<<'|'<<endl;
	}
    p=p->next;
	}
}
void showone_wheremany(Node *p,int *selnum,char *findvalue,int Record2,int num)//条件查询多列查询
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
void Delete(Node *p,int Record,char *findvalue)//删除
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
void Update(Node *p,int Record,char *findvalue)//修改
	   {
		   while(p->next)
		   {
		   strcpy(p->next->data[Record],findvalue);
		   p=p->next;
		   }
	   }
void seltime(double start,double finish)//计算查询时间
{
	double time;//查询时间
	time=(double)(finish-start)/(double)CLK_TCK;
	cout<<"本次查询用时"<<time<<"秒"<<endl;
}
int main()
{
	char input[100];//输入
	char Attribute[20];//用于查找列名
    char **attribute;//列名
	int i=0,j=0,k=0,l=0;
	int record=0;//记录字符位置
	int Record=-1;//记录列序号
	int num=0;//逗号个数
	bool flag=0;//标记是否建表
	int *selnum;//查询的列数
	char end=0;//输入结束标记
	Node *p,*s;//链表头节点
	char Name[10];//识别表名
	char findattri[20];//记录查询的条件属性
	char findvalue[20];//记录查询的条件属性的值
	int Record2=-1;//记录条件列的序号
	clock_t start,finish;//计算查询时间
	char End=0;//整个程序结束标记
	int *innum;//记录插入的列数
	char **invalue;
	cout<<"欢迎使用!"<<endl<<endl;
	cout<<"制作人:"<<endl;
	cout<<"孙童凯,贾玲,王静,周家琛"<<endl<<endl;
	cout<<"请输入SQL语言:"<<endl;
    while(true)
	{cin.getline(input,250,'\n');//输入SQL语言
	if(selfunc(input,flag)==-1)//异常
	{return 0;}
	if(selfunc(input,flag)==1)//选择建表功能
	{
		cout<<"选择建表功能"<<endl;
		for(i=13;input[i]!='(';i++)//识别表名
	{name[i-13]=input[i];}
	name[i-13]='\0';
	record=i;//左括号位置
	if(strcmp(name,"")==0)
	{cout<<"未输入表名!"<<endl;
	return 0;
	}
	else
	{cout<<"表名为:"<<name<<endl;}
		for(i=0;input[i]!='(';i++)
	{}
    record=i;//左括号位置
	num=0;
	for(i=record+1;input[i]!=')';i++)//数逗号个数=列数-1
	{if(input[i]==',')
	{num++;}
	}
	column=num;
	attribute=new char*[column+1];
	for(i=0;i<column+1;i++)
	{attribute[i]=new char[20];}
	if(num==0)//只有一个列
	{j=0;
	l=0;
	for(i=record+1;input[i]!=' ';i++)
	{attribute[j][l]=input[i];
	l++;
	}
	attribute[j][l]='\0';
	}
	else
	{while(num>0)//有多个列
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
	record=i;//逗号位置
	}
	for(i=record+1;input[i]!=' ';i++)//最后一个列
	{attribute[j][l]=input[i];
	l++;
	}
	attribute[j][l]='\0';
	}
	cout<<"表的各个列为:"<<endl;
	drawtable(column);
	for(i=0;i<column+1;i++)
	{cout<<setfill(' ')<<setw(15)<<attribute[i]<<'|';}
	cout<<endl;
	drawtable(column);
	cout<<endl;
	flag=1;//已完成建表
	}
	if(selfunc(input,flag)==6)//选择建立索引功能
	{cout<<"请按行输入数据:"<<endl;
	for(i=16;input[i]!=';';i++)
	    {Name[i-16]=input[i];}
	    Name[i-16]='\0';
	    if(strcmp(Name,name)!=0)
	    {cout<<"表名不正确!"<<endl;
	    return 0;
	    }
	p=(Node*)malloc(sizeof(Node));
	p->next=NULL;
	while(end!='\r')
	{s=(Node*)malloc(sizeof(Node));
	s->data=new char*[column+1];
	for(i=0;i<column+1;i++)
	{s->data[i]=new char[20];}//一个行记录对应一个字符数组
	for(i=0;i<column+1;i++)//输入各列数据
	{cin.getline(s->data[i],20,'\n');}
	cout<<"请输入下一行数据,或按回车键结束输入:"<<endl;
	s->next=p->next;
	p->next=s;
	end=getch();//回车键结束输入
	}
	cout<<"已完成建表"<<endl;
	cout<<"各列数据如下:"<<endl;
	drawtable(column);
	for(i=0;i<column+1;i++)
	{cout<<setfill(' ')<<setw(15)<<attribute[i];
	cout<<'|';
	}
	cout<<endl;
	drawtable(column);
	showall(p,column);//显示各列数据
	drawtable(column);
	Save("TextFile.txt",p,column,attribute);
	cout<<endl;
	}
	if(selfunc(input,flag)==2)//选择查询功能
	{
		cout<<"选择查询功能"<<endl;
		start=clock();
		for(i=0;input[i]!=' ';i++)
		{}
	record=i;//空格位置
		if(findwhere(input)==0)//判断表名是否正确//没有WHERE
	{for(i=space+1;input[i]!=';';i++)
	{Name[i-space-1]=input[i];}
	Name[i-space-1]='\0';
	if(strcmp(Name,name)!=0)
	{cout<<"表名不正确!"<<endl;
	return 0;
	}
	}
	else//有WHERE
	{for(i=space-1;input[i]!=' ';i--)
	{}
	j=i;//表名后的空格
	for(i=j-1;input[i]!=' ';i--)
	{}
	j=i;//FROM后的空格
	for(i=j+1;input[i]!=' ';i++)
	{Name[i-j-1]=input[i];}
	Name[i-j-1]='\0';
	if(strcmp(Name,name)!=0)
	{cout<<"表名不正确!"<<endl;
	return 0;
	}
	}
	num=0;
	for(i=record+1;input[i]!='\0';i++)//要查询的列数-1
	{if(input[i]==',')
	{num++;}
	}
	k=num;
	Record=-1;
	if(findwhere(input)==0)//没有WHERE
	{if(k==0)//只查询一个列
	{for(i=record+1;input[i]!=' ';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"查询的列不存在!"<<endl;
	return 0;}
	drawtable(num);
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	drawtable(num);
	showone(p,Record);//输出查询结果
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	else//查询多个列
	{drawtable(num);
	selnum=new int[num+1];
	l=0;
	while(k>0)
	{for(i=record+1;input[i]!=',';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	record=i;//逗号的位置
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"查询的列不存在!"<<endl;
	return 0;
	}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|';
	selnum[l]=Record;
	l++;
	k--;
	Record=-1;
	}
	for(i=record+1;input[i]!=' ';i++)//识别语句中最后一列
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"查询的列不存在!"<<endl;
	return 0;}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	selnum[l]=Record;
	drawtable(num);
	showone_many(p,selnum,num);//输出查询结果
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	}
	Record=-1;
	if(findwhere(input)==1)//有WHERE
	{if(k==0)//只查询一个列
	{for(i=record+1;input[i]!=' ';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(i=0;input[i]!=';';i++)
	{}
	j=i;//分号位置
	for(i=j;input[i]!='=';i--)
	{}
	j=i;//等于号位置
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
	{cout<<"查询的列不存在!"<<endl;
	return 0;}
	drawtable(num);
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	drawtable(num);
	showone_where(p,Record,findvalue,Record2);
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	else//查询多个列
	{drawtable(num);
	selnum=new int[num+1];
	l=0;
	while(k>0)
	{for(i=record+1;input[i]!=',';i++)
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	record=i;//逗号的位置
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"查询的列不存在!"<<endl;
	return 0;
	}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|';
	selnum[l]=Record;
	l++;
	k--;
	Record=-1;
	}
	for(i=record+1;input[i]!=' ';i++)//识别语句中最后一列
	{Attribute[i-record-1]=input[i];}
	Attribute[i-record-1]='\0';
	for(j=0;j<column+1;j++)
	{if(strcmp(Attribute,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"查询的列不存在!"<<endl;
	return 0;}
	cout<<setfill(' ')<<setw(15)<<Attribute<<'|'<<endl;
	selnum[l]=Record;
	for(i=0;input[i]!=';';i++)
	{}
	j=i;//分号位置
	for(i=j;input[i]!='=';i--)
	{}
	j=i;//等于号位置
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
	{cout<<"查询的列不存在!"<<endl;
	return 0;}
	drawtable(num);
	showone_wheremany(p,selnum,findvalue,Record2,num);
	drawtable(num);
	finish=clock();
	seltime(start,finish);
	}
	}
	}
	if(selfunc(input,flag)==3)//选择插入功能
	{
		cout<<"选择插入功能"<<endl;
		for(i=12;input[i]!='(';i++)
	    {Name[i-12]=input[i];}
	    Name[i-12]='\0';
		record=i;//左括号的位置
	    if(strcmp(Name,name)!=0)
	    {cout<<"表名不正确!"<<endl;
	    return 0;
	    }
        num=0;
		Record=-1;
	    for(i=0;input[i]!=')';i++)//要插入的列数-1
	    {if(input[i]==',')
	    {num++;}
	    }
	    k=num;
		if(k==0)//只插入一列
		{for(i=record+1;input[i]!=')';i++)
	    {findattri[i-record-1]=input[i];}
	    findattri[i-record-1]='\0';
        for(i=0;input[i]!=')';i++)
		{}
		record=i;//第一个右括号的位置
		for(i=record+1;input[i]!='(';i++)
		{}
		record=i;//第二个左括号的位置
		for(i=record+1;input[i]!=')';i++)
		{findvalue[i-record-1]=input[i];}
		findvalue[i-record-1]='\0';
	    for(j=0;j<column+1;j++)
	    {if(strcmp(findattri,attribute[j])==0)
	    {Record=j;}
	    }
	    if(Record==-1)
	    {cout<<"查询的列不存在!"<<endl;
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
		else//插入多列
		{l=0;
		innum=new int[num+1];
	    while(k>0)
	    {for(i=record+1;input[i]!=',';i++)
	    {findattri[i-record-1]=input[i];}
	    findattri[i-record-1]='\0';
	    record=i;//逗号的位置
	    for(j=0;j<column+1;j++)
	    {if(strcmp(findattri,attribute[j])==0)
	    {Record=j;}
	    }
	    if(Record==-1)
	    {cout<<"查询的列不存在!"<<endl;
	    return 0;
	    }
	    innum[l]=Record;
	    l++;
	    k--;
	    Record=-1;
		}
	    for(i=record+1;input[i]!=')';i++)//识别语句中最后一列
		{Attribute[i-record-1]=input[i];}
	    Attribute[i-record-1]='\0';
	    for(j=0;j<column+1;j++)
		{if(strcmp(Attribute,attribute[j])==0)
		{Record=j;}
		}
	    if(Record==-1)
		{cout<<"查询的列不存在!"<<endl;
	    return 0;}
	    innum[l]=Record;
	    k=num;
	    invalue=new char*[num+1];
	    for(i=0;i<num+1;i++)
		{invalue[i]=new char[10];}
        for(i=0;input[i]!=')';i++)
		{}
		record=i;//第一个右括号的位置
		for(i=record+1;input[i]!='(';i++)
		{}
		record=i;//第二个左括号的位置
		l=0;
		while(k>0)
	    {for(i=record+1;input[i]!=',';i++)
	    {invalue[l][i-record-1]=input[i];}
	    invalue[l][i-record-1]='\0';
	    record=i;//逗号的位置
	    l++;
	    k--;
		}
		for(i=record+1;input[i]!=')';i++)//识别语句中最后一列
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
	if(selfunc(input,flag)==4)//选择删除功能
	{cout<<"选择删除功能！"<<endl;
	for(i=12;input[i]!=' ';i++)
	{Name[i-12]=input[i];}
	Name[i-12]='\0';
	if(strcmp(Name,name)!=0)
	{cout<<"表名不正确！"<<endl;
	return 0;
	}
	Record=-1;
		for(i=0;input[i]!=';';i++)
		{}
		j=i;//分号位置
		for(i=j;input[i]!=' ';i--)
		{}
		j=i;//空格位置
		for(i=j+1;input[i]!='=';i++)
		{findattri[i-j-1]=input[i];}
		findattri[i-j-1]='\0';
		j=i;//等号位置
		for(i=j+1;input[i]!=';';i++)
		{findvalue[i-j-1]=input[i];}
		findvalue[i-j-1]='\0';
		for(j=0;j<column+1;j++)
		{if(strcmp(findattri,attribute[j])==0)
		{Record=j;}
		}
		if(Record==-1)
		{cout<<"删除的列不存在!"<<endl;
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
	if(selfunc(input,flag)==5)//选择修改功能
{
cout<<"选择修改功能"<<endl;
for(i=7;input[i]!=' ';i++)
    {Name[i-7]=input[i];}
    Name[i-7]='\0';
record=i;//空格的位置
    if(strcmp(Name,name)!=0)
    {cout<<"表名不正确!"<<endl;
    return 0;
    }
	Record=-1;
   for(i=0;input[i]!=';';i++)
		{}
		j=i;//分号位置
		for(i=j;input[i]!=' ';i--)
		{}
		j=i;//空格位置
		for(i=j+1;input[i]!='=';i++)
	{findattri[i-j-1]=input[i];}
	findattri[i-j-1]='\0';
	j=i;//等号位置
		for(i=j+1;input[i]!=';';i++)
		{findvalue[i-j-1]=input[i];}
		findvalue[i-j-1]='\0';	   
	for(j=0;j<column+1;j++)
	{if(strcmp(findattri,attribute[j])==0)
	{Record=j;}
	}
	if(Record==-1)
	{cout<<"查询的列不存在!"<<endl;
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
	cout<<"继续输入SQL语言或按ESC退出程序"<<endl;
	End=getch();//按ESC键结束程序
    if(End==27)
	{return 0;}
	}
	return 0;
}