// CCC 2014 Stage 2
// Day 2, Problem 2: Early Exam Evacuation
// Jacob Plachta

#define DEBUG 0

#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <sstream>
using namespace std;

#define LL long long
#define LD long double
#define PR pair<int,int>

#define Fox(i,n) for (i=0; i<n; i++)
#define Fox1(i,n) for (i=1; i<=n; i++)
#define FoxI(i,a,b) for (i=a; i<=b; i++)
#define FoxR(i,n) for (i=(n)-1; i>=0; i--)
#define FoxR1(i,n) for (i=n; i>0; i--)
#define FoxRI(i,a,b) for (i=b; i>=a; i--)
#define Foxen(i,s) for (i=s.begin(); i!=s.end(); i++)
#define Min(a,b) a=min(a,b)
#define Max(a,b) a=max(a,b)
#define Sz(s) int((s).size())
#define All(s) (s).begin(),(s).end()
#define Fill(s,v) memset(s,v,sizeof(s))
#define pb push_back
#define mp make_pair
#define x first
#define y second

template<typename T> T Abs(T x) { return(x<0 ? -x : x); }
template<typename T> T Sqr(T x) { return(x*x); }
string plural(string s) { return(Sz(s) && s[Sz(s)-1]=='x' ? s+"en" : s+"s"); }

const int INF = (int)1e9;
const double EPS = 1e-9;
const LD PI = acos(-1.0);

#if DEBUG
#define GETCHAR getchar
#else
#define GETCHAR getchar_unlocked
#endif

bool Read(int &x)
{
	char c,r=0,n=0;
	x=0;
		for(;;)
		{
			c=GETCHAR();
				if ((c<0) && (!r))
					return(0);
				if ((c=='-') && (!r))
					n=1;
				else
				if ((c>='0') && (c<='9'))
					x=x*10+c-'0',r=1;
				else
				if (r)
					break;
		}
		if (n)
			x=-x;
	return(1);
}

int N;
int BLT[1000001];

void update(int i,int v)
{
	for (; i<=N; i+=(i&-i))
		BLT[i]+=v;
}

int query(int i)
{
	int v=0;
		for (; i; i-=(i&-i))
			v+=BLT[i];
	return(v);
}

int main()
{
		if (DEBUG)
			freopen("in.txt","r",stdin);
	int M,A,B;
	int i,j,k,c1,c2;
	LL v,ans;
	static int row[1000001],cnt1[1000001],cnt2[1000001];
	static LL sum1[1000002],sum2[1000002];
	static char col[1000001];
	static bool vac[1000001][6]={0};
	static PR ppl[1000001];
	Read(N),Read(M),Read(A),Read(B);
		Fox(i,M)
			scanf("%d%c",&row[i],&col[i]);
		Fox(k,M)
		{
			//vacate this seat
			vac[row[k]][col[k]-'A']=1;
				if ((col[k]=='C') || (col[k]=='D'))
					update(row[k],1);
			//count people in the way for both lavatories
			c1=0;
				if ((col[k]=='A') && (!vac[row[k]][1]))
					c1++;
				if ((col[k]=='F') && (!vac[row[k]][4]))
					c1++;
			c2=c1;
			c1+=2*row[k]-query(row[k]);
			c2+=2*(N-row[k]+1)-(query(N)-query(row[k]-1));
			cnt1[k]=c1;
			cnt2[k]=c2;
			ppl[k]=mp(c1-c2,k);
		}
	//sort people by how much better it is for them to go to the front
	sort(ppl,ppl+M);
	//compute prefix/postfix sums
		Fox1(i,M)
			sum1[i]=sum1[i-1]+cnt1[ppl[i-1].y];
		FoxR1(i,M)
			sum2[i]=sum2[i+1]+cnt2[ppl[i-1].y];
	//try all numbers of people to send to the front
	ans=(LL)INF*INF;
		Fox(i,M+1)
		{
			j=M-i;
			v=A*(sum1[i]+sum2[i+1]) + B*((LL)i*(i-1)/2 + (LL)j*(j-1)/2);
			Min(ans,v);
		}
	printf("%lld\n",ans);
	return(0);
}
