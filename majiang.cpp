//万:a   筒：b    条：c    风（东南西北）：d    箭（中白发）：e
#include<bits/stdc++.h>
using namespace std;
const int _13 = 13,N = 1145;
struct pai
{
	int a;//数码
	char type;//哪种
}ps[N],a[N];
int cnt = _13;//手牌数
int dui,ke,da;//对子、刻子、搭子
void init()
{
	srand(time(0));
	int cnt = 0;
	int i,j;
	for(i=1;i<=9;i++)
		for(j=1;j<=4;j++)
			ps[++cnt] = {i,'a'};
	for(i=1;i<=9;i++)
		for(j=1;j<=4;j++)
			ps[++cnt] = {i,'b'};
	for(i=1;i<=9;i++)
		for(j=1;j<=4;j++)
			ps[++cnt] = {i,'c'};
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			ps[++cnt] = {i,'d'};
	for(i=1;i<=3;i++)
		for(j=1;j<=4;j++)
			ps[++cnt] = {i,'e'};
	random_shuffle(ps+1,ps+1+cnt);
	return;
}
bool cmp(pai a,pai b)//排序
{
	if(a.type==b.type)
		return a.a<b.a;
	return a.type<b.type;
}
void print(pai a[],int l)
{
	int i;
	for(i=1;i<=l;i++)
		cout<<a[i].a<<a[i].type<<' ';
	cout<<endl;
	
	i = 1;
	
	if(a[i].type!='a')
		cout<<"_";
	else
	{
		for(;a[i].type=='a';i++)
			cout<<a[i].a;
	}
	cout<<' ';
	
	if(a[i].type!='b')
		cout<<"_";
	else
	{
		for(;a[i].type=='b';i++)
			cout<<a[i].a;
	}
	cout<<' ';
	
	if(a[i].type!='c')
		cout<<"_";
	else
	{
		for(;a[i].type=='c';i++)
			cout<<a[i].a;
	}
	cout<<' ';
	
	if(a[i].type!='d')
		cout<<"_";
	else
	{
		for(;a[i].type=='d';i++)
			cout<<a[i].a;
	}
	cout<<' ';
	
	if(a[i].type!='e')
		cout<<"_";
	else
	{
		for(;a[i].type=='e';i++)
			cout<<a[i].a;
	}
	cout<<' ';
	
	cout<<endl;
	return;
}
void ask()
{
	printf("请选择自己输入手牌（1）还是程序随机分配（2）？\n");
	int type;
	cin>>type;
	if(type==1)
	{
		int cnt = 0;
		printf("为保证方便，你只需要输入 5 个数字串，表示每个牌的类型，若没有，则输入一个下划线（_）\n");
		int i;
		for(i=1;i<=5;i++)
		{
			string s;
			cin>>s;
			if(s=="_")
				continue;
			int j;
			for(j=0;j<s.size();j++)
			{
				a[++cnt] = {s[j]-'0',char(i+96)};
			}
		}
	}
	else
	{
		int i;
		for(i=1;i<=_13;i++)
			a[i] = ps[i];
	}
	sort(a+1,a+1+_13,cmp);
	print(a,_13);
}
int t[N],tmp[N];
bool bj;
bool check(int n)
{
	for(int i = 1; i <= n; i++)
	{
		if(t[i] >= 2) //只有凑成对子以上个数时才能胡牌。
		{
			bool ok = 1; //进行标记是否找到。
			t[i] -= 2; //将其当做对子。
			for(int j = 1; j <= n + 2; j++)
				tmp[j] = t[j]; //不能改变原来数组的值。
			for(int j = 1; j <= n + 2; j++)
			{
				if(tmp[j] < 0) //如果小于0则代表不能胡牌，直接退出循环，进行下一个对子的判断。
				{
					ok = 0;
					break;
				}
				tmp[j] %= 3; //刻子
				tmp[j + 1] -= tmp[j]; //顺子
				tmp[j + 2] -= tmp[j]; //顺子
			}
			t[i] += 2;
			if(ok)
				return 1;
		}
	}
	return 0;
}
int tings[N],c_ting;
int killed;
bool ch_ting(int a[],int n,int m)
{
	memset(tings,0,sizeof tings);
	memset(t,0,sizeof t);
	memset(tmp,0,sizeof tmp);
	c_ting = 0;
	bj = 0;
	int i;
	for(i=1;i<=m;i++)
		t[a[i]]++;
	for(i=1;i<=n;i++)
	{
		t[i]++;
		if(check(n))
			bj = 1,tings[++c_ting] = i;
		t[i]--;
	}
	return bj;
}
bool check_hu(int a[],int n,int m)
{
	int tn = n,tm = m;
	if(m==0)
		return 1;
	//a 是当前数组，n 是牌数范围，一般是 1~9，m 是序列长度
	if((m-2)%3==0)
	/*
	判断 1 1 2 3 4 胡牌了吗？
	等价于砍掉 4，变成 1 1 2 3，此时听牌 1,4，只要看看这两个数里面有没有 4 即可
	*/
	{
		killed = a[m];
		m--;
	}
	else if((m-1)%3==0)//1 1 2 3，直接判断就行，不用改
		;
	else
	/*
	判断 1 2 3 4 5 6 胡牌了吗？
	等价于砍掉 6，变成 1 2 3 4 5，然后加上两个 11，变成 1 2 3 4 5 11 11，此时听牌 3,6，只要看看这两个数里面有没有 6 就可以了
	*/
	{
		killed = a[m];
		m--;
		n = 11;
		a[++m] = 11;
		a[++m] = 11;
	}
	bool ting = ch_ting(a,n,m);
	if(!ting)
		return 0;
	int i;
//	cout<<c_ting<<endl;
//	for(i=1;i<=c_ting;i++)
//		cout<<tings[i]<<' ';cout<<endl;
	for(i=1;i<=c_ting;i++)
		if(tings[i]==killed)
			return 1;
	return 0;
}
bool special(pai a[],int cnt)
{
	bool fl = 0;
	//小七对
	int i;
	int dui = 0;
	for(i=1;i<=5;i++)
	{
		int j;
		int t[N] = {};//桶
		for(j=1;j<=cnt;j++)
			if(a[j].type==char(i+96))
				t[a[j].a]++;
		for(j=1;j<=9;j++)
			if(t[j]%2==0&&t[j]!=0)
				dui += t[j]/2;
	}
	if(dui==7)
		return 1;
	return 0;
}
bool biggest_check_hu(pai a[],int cnt)
{
	bool sp = special(a,cnt);//先把小七对这些逆天的东西判断掉
	if(sp)
		return sp;
	//检验万、筒、条分别是否胡牌（注意要用 b 数组！）
	bool hu = 1;
	int i;
	for(i=1;i<=3;i++)
	{
		int t[N] = {};//储存哪一类的牌
		int j;
		int c = 0;//哪一类的牌的个数
		for(j=1;j<=cnt;j++)
			if(a[j].type==char(i+96))
				t[++c] = a[j].a;
		hu &= check_hu(t,9,c);
	}
	//检验风、箭
	int dui = 0,ke = 0;
	for(i=4;i<=5;i++)
	{
		int t[N] = {};//桶
		int j;
		for(j=1;j<=cnt;j++)
			if(a[j].type==char(i+96))
				t[a[j].a]++;
		for(j=1;j<=4;j++)
		{
			if(t[j]%2==0&&t[j]>0)
				dui++;
			if(t[j]==3)
				ke++;
		}
	}
	if(dui>=2)
		hu = 0;
	return hu;
}
void calc(pai a[],int cnt)
{
	;
}
int kill(pai a[],int n,pai x,int pos)
{
	pai b[N] = {};
	int i;
	for(i=1;i<=n;i++)
		b[i] = a[i];
	for(i=pos;i<n;i++)
		b[i] = b[i+1];
	
}
string da3(pai a[],int cnt)//打是3声的！
{
	int i;
	int ma = 0;
	string ans;
	for(i=1;i<=cnt;i++)
	{
		int nw = kill(a,cnt,a[i],i);//打掉 a_i 后可以进张数量
		if(nw>ma)
			ma = nw,ans = (a[i].a+'0')+a[i].type;
	}
}
void add()
{
	printf("接下来请一直输入当前摸到的牌，一直到 EOF\n");
	string nw;
	while(cin>>nw)
	{
		pai b[N] = {};
		int i;
		cnt++;
		for(i=1;i<=_13;i++)
			b[i] = a[i];
		b[cnt] = {nw[0]-'0',nw[1]};
		sort(b+1,b+1+cnt,cmp);
		calc(b,cnt);
		print(b,cnt);
		bool hu = biggest_check_hu(b,cnt);
		if(hu)
		{
			cout<<"你胡了！"<<endl;
			exit(0);
		}
		string fudge = da3(b,cnt);
	}
	return;
}
int main()
{
	init();
	ask();
	add();
	return 0;
}
