/*************************************************************** 
 
* 
版权所有 (C)2014, 五十风 
 
* 
程序名称：北京地铁导航 
 
* 
作    者：五十风 
 
*  
完成日期：2015.1.20 

 
***************************************************************/  

#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include <windows.h>
#include<conio.h>
using namespace std;

#define N 200
const double V=0.555;
int n;
struct road
{
	int des;//终点站名
	double dis;//距离
};
//本站能到达的其他站的站名
struct subway
{
	subway()
	{count=0;}
	int count;
	road lu[6];
};
//起点到达其他点的最短路
struct min_road
{
	min_road()
	{
		count=0;
		dis=0.0;
	}
	int count;
	double dis;
	int transit[N];//经过的点，包含起点，与目的地

};
struct s_e
{
	int s_to_des;
	int e_to_des;
};
struct cmp
{
	bool operator()(road x,road y)
    {
        return x.dis<y.dis;
    }
    
};


int sort_road(subway *arry,int n)
{
	int i=0;
	for(i=1;i<n;i++)
	{
		if(arry[i].count)
			sort(arry[i].lu,arry[i].lu+arry[i].count,cmp());
	}
	return 0;
}

int find_min(subway *arry,bool *vis,min_road *_dis,int n)
{
	int i,j,s_dian,e_dian;
	double min,temp;
	bool f=true;
	for(i=1;i<n;i++)
	{
		if(vis[i])
		{
			subway &dian=arry[i];
			for(j=0;j<dian.count;j++)
			{
				if(!vis[dian.lu[j].des])
				{
					temp=_dis[i].dis+dian.lu[j].dis;
					if(f)
					{
						f=false;
						s_dian=i;
						e_dian=dian.lu[j].des;
						min=temp;
					}
					else
					if(min>temp)
					{
						s_dian=i;
						e_dian=dian.lu[j].des;
						min=temp;
					}
					break;
				}
			}
		}
	}
	if(f)
		return 0;
	vis[e_dian]=true;
	for(i=0;i<_dis[s_dian].count;i++)
	{
		_dis[e_dian].transit[i]=_dis[s_dian].transit[i];
	}
	_dis[e_dian].transit[i]=e_dian;
	_dis[e_dian].count=_dis[s_dian].count+1;
	_dis[e_dian].dis=min;
	return e_dian;
}
s_e Dijkstra(subway *arry,bool *s_vis,bool *e_vis,min_road *s_dis,min_road *e_dis,int start,int end,int n)
{
	int temp1,temp2,i,j;
	s_e temp;
	for(i=1;i<n;i++)
	{
		temp1=find_min(arry,s_vis,s_dis,n);
		if(temp1==end)
		{
			temp.s_to_des=temp1;
			temp.e_to_des=0;
			return temp;
		}
		temp2=find_min(arry,e_vis,e_dis,n);
		if(temp2==start)
		{
			temp.e_to_des=temp2;
			temp.s_to_des=0;
			return temp;
		}
		if(temp1==temp2 &&temp1!=0)
		{
			temp.s_to_des=temp1;
			temp.e_to_des=temp2;
			return temp;
		}
		for(j=0;j<n;j++)
		{
			if(e_vis[j] && s_vis[j])
			{
				temp.s_to_des=j;
				temp.e_to_des=j;
				return temp;
			}

		}
	}
	temp.s_to_des=0;
	temp.e_to_des=0;
	return temp;
}
void input(subway *arry,int start,int end,double dis)
{
	int &cc=arry[start].count;
	int &bb=arry[end].count;
	arry[start].lu[cc].des=end;
	arry[start].lu[cc].dis=dis;
		cc++;
	arry[end].lu[bb].des=start;
	arry[end].lu[bb].dis=dis;
		bb++;
}
void show(min_road a,bool if_s,bool if_second)
{
	int i,num;
	bool f=0;
	string s;
	ifstream fin;
	
	if(if_s) 
		for(i=0;i<a.count;i++)
		{
			f=0;
			fin.open("no.txt");
			while(fin>>num)
			{
				fin>>s;
				if(num==a.transit[i])
				{
					f=1;
					break;
				}
			}
			fin.close();
			if(f)
				cout<<s<<" ";
			else
				cout<<"\n错误："<<"找不到"<<a.transit[i]<<"no.txt被修改或删除\n";
		}
	else 
	{
		i=a.count-1;
		if(if_second)
			i--;
		for(;i>=0;i--)
		{
			f=0;
			fin.open("no.txt");
			while(fin>>num)
			{
				fin>>s;
				if(num==a.transit[i])
				{
					f=1;
					break;
				}
			}
			fin.close();
			if(f)
				cout<<s<<" ";
			else
				cout<<"\n错误："<<"找不到"<<a.transit[i]<<"no.txt被修改或删除\n";
		}
	}
	
	
}
bool In(wchar_t start, wchar_t end, wchar_t code)
{
if (code >= start && code <= end)
{
return true;
}
return false;
}

char convert(wchar_t n)
{
if (In(0xB0A1,0xB0C4,n)) return 'a';
if (In(0XB0C5,0XB2C0,n)) return 'b';
if (In(0xB2C1,0xB4ED,n)) return 'c';
if (In(0xB4EE,0xB6E9,n)) return 'd';
if (In(0xB6EA,0xB7A1,n)) return 'e';
if (In(0xB7A2,0xB8c0,n)) return 'f';
if (In(0xB8C1,0xB9FD,n)) return 'g';
if (In(0xB9FE,0xBBF6,n)) return 'h';
if (In(0xBBF7,0xBFA5,n)) return 'j';
if (In(0xBFA6,0xC0AB,n)) return 'k';
if (In(0xC0AC,0xC2E7,n)) return 'l';
if (In(0xC2E8,0xC4C2,n)) return 'm';
if (In(0xC4C3,0xC5B5,n)) return 'n';
if (In(0xC5B6,0xC5BD,n)) return 'o';
if (In(0xC5BE,0xC6D9,n)) return 'p';
if (In(0xC6DA,0xC8BA,n)) return 'q';
if (In(0xC8BB,0xC8F5,n)) return 'r';
if (In(0xC8F6,0xCBF0,n)) return 's';
if (In(0xCBFA,0xCDD9,n)) return 't';
if (In(0xCDDA,0xCEF3,n)) return 'w';
if (In(0xCEF4,0xD188,n)) return 'x';
if (In(0xD1B9,0xD4D0,n)) return 'y';
if (In(0xD4D1,0xD7F9,n)) return 'z';
return '\0';
}

char pinyin(string sChinese)
{
	char chr[3];
	wchar_t wchr = 0;
	char buff=0x00;
	int j=0,i=0;
	memset(chr, 0x00, sizeof(chr));
	chr[0] = sChinese[j++];
	chr[1] = sChinese[j++];
	chr[2] = '\0';
	wchr = 0;
	wchr = (chr[0] & 0xff) << 8;
	wchr |= (chr[1] & 0xff);
	buff = convert(wchr);
	return buff;

}

int find_num(string s)
{
	char c;
	int num;
	string a;
	c=pinyin(s);
	a=c;
	a="subway\\"+a+".txt";
	ifstream fin;
	
	fin.open(a.c_str());
	while(fin>>a)
	{
		fin>>num;
		if(a==s)
		{
			fin.close();
			return num;
		}
	}
	fin.close();
	return -1;
}

void meun()
{
	int i=0,j;
		char a=3,b=5;
		cout<<"\t\t";
		for(j=1;j<10;j++)
		{
			if(i==0) 
			{
				if(!(j&1)) cout<<a<<" ";
				else cout<<b<<" ";
			}
			else 
			{
				if((j&1)) cout<<a<<" ";
				else cout<<b<<" ";
			}
		}
		cout<<endl;
		cout<<"\t\t";

		if(i==1) cout<<a;
		else cout<<b;

		cout<<"  北京地铁导航 ";
		if(i==0) cout<<a;
		else cout<<b;
		cout<<endl;
		cout<<"\t\t";
		for(j=1;j<10;j++)
		{
						if(i==0) 
			{
				if(!(j&1)) cout<<a<<" ";
				else cout<<b<<" ";
			}
			else 
			{
				if((j&1)) cout<<a<<" ";
				else cout<<b<<" ";
			}
		}
		cout<<endl;
		cout<<"\n\t1.查找最佳乘坐方案\t2.查看支持站名\n";
		cout<<"\t3.新增站点\t\t4.新增路线\n\t0.退出\n\n";
}
int money(double a)
{
	int m;

	if(a>0.0 && a<=6.0) return 3;
	if( a>6.0 &&a<=12.0) return 4;
	if(a>12.0 &&a<=32.0)
	{
		m=4;
		a-=12.0;
		m++;
		while(a>0)
		{
			a-=10;
			m++;
		}
		return m;
	}
	if(a>32.0)
	{
		m=6;
		a-=32.0;
		m++;
		while(a>0)
		{
			a-=20;
			m++;
		}
		return m;

	}
}
void newsubway()
{
	ifstream fin;
	int temp_num;
	fin.open("num.txt");
	fin>>temp_num;	
	temp_num++;
	fin.close();

	ofstream fout,fout2,fout3;
	cout<<"输入新增站点名:";
	string s;
	string name;
	cin>>s;
	string c;
	c=pinyin(s);
	name="subway\\"+c+".txt";
	fout.open(name.c_str(),ios::app);
	fout<<s<<" ";
	fout<<temp_num<<endl;
	fout.close();

	fout2.open("no.txt",ios::app);
	fout2<<temp_num<<" ";
	fout2<<s<<"\n";
	fout2.close();

	fout3.open("num.txt");
	fout3<<temp_num;
	fout3.close();
	
}

void newroad(subway *arry)
{
	subway *a=arry;
	ofstream fout;
	string one,two;
	double dis;
	int s,e;
	cout<<"输入新增路线，格式为:站名 站名 路程。\n如：天安门西 天安门东 0.9\n";
	cin>>one;
	cin>>two;
	cin>>dis;
	s=find_num(one);
	e=find_num(two);
	fout.open("road.txt",ios::app);
	fout<<s<<" "<<e<<" "<<dis<<" "<<endl;
	fout.close();
	input(a,e,s,dis);
}
int main()
{
	SetConsoleTitle("北京地铁导航");
	system("COLOR F0");	
	subway arry[N];
	
	int i,a,b,choose;
	double c,min;
	string one,two;
	int start,end;
	ifstream fin;
	ifstream fin2;
	fin2.open("num.txt");
	fin2>>n;
	n++;
	fin2.close();
	fin.open("road.txt");
	for(i=0;i<n-2;i++)
	{
		fin>>a;
		fin>>b;
		fin>>c;
		input(arry,a,b,c);
	}
	fin.close();
	sort_road(arry,n);
	while(1)
	{
		meun();
		cout<<"输入选择:";
		cin>>choose;
		if(choose==0)
		{
			cout<<endl<<endl;
			break;
		}
		if(choose==3)
		{
			newsubway();
			fflush(stdin);
			cout<<"按回车键继续";
			getchar();
			system("cls");
		}
		if(choose==4)
		{
			newroad(arry);
			fflush(stdin);
			cout<<"按回车键继续";
			getchar();
			system("cls");
		}
		if(choose==2)
		{
			cout<<endl;
			int a;
			string s;
			ifstream fin;
			fin.open("no.txt");
			while(fin>>a)
			{
				fin>>s;
				cout<<a<<"."<<s<<" ";
			
			}	cout<<endl<<endl;
			fin.close();
			fflush(stdin);
			cout<<"按回车键继续";
			getchar();
			system("cls");
			continue;
		}
		if(choose==1)
		{
		bool s_vis[N],e_vis[N];
		min_road s_dis[N],e_dis[N];
		s_e temp;
		min=0.0;
		cout<<"输入起点:";
		cin>>one;
		cout<<"输入终点:";
		cin>>two;
		start=find_num(one);
		end=find_num(two);
		if(start==-1 || end==-1)
		{
			cout<<"输入的地铁站错误"<<endl;
			continue;
		}
		memset(s_vis,false,sizeof(s_vis));
		memset(e_vis,false,sizeof(e_vis));
		s_dis[start].count++;
		s_dis[start].transit[0]=start;
		e_dis[end].count++;
		e_dis[end].transit[0]=end;
		s_vis[start]=true;
		e_vis[end]=true;
		temp=Dijkstra(arry,s_vis,e_vis,s_dis,e_dis,start,end,n);
		cout<<"\n乘坐路线为：";
		if(temp.s_to_des!=0)
		{
			min+=s_dis[temp.s_to_des].dis;
			show(s_dis[temp.s_to_des],true,false);
			if(temp.e_to_des!=0)
			{
				min+=e_dis[temp.e_to_des].dis;
				show(e_dis[temp.e_to_des],false,true);
			}
		}
		else
		{
			min+=e_dis[temp.e_to_des].dis;
			show(e_dis[temp.e_to_des],false,false);
		}
		cout<<"\n长度："<<min<<endl;
		cout<<"所需时间："<<(int)(min/V)+2<<"分钟"<<endl;
		cout<<"所需钱："<<money(min)<<"元"<<endl<<endl;
		fflush(stdin);
		cout<<"按回车键继续";
			getchar();
			system("cls");
		}
	}

	return 0;
}