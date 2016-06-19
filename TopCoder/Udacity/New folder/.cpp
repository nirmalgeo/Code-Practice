
#include<sstream>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<stdio.h>
#include<queue>
#define si(n) scanf("%d",&n)
#define sll(n) scanf("%lld",&n)
#define mod 1000000007 // 10**9 + 7
//#define INF 1e6
#define FOR(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define LFOR(i,a,b) for(long long int (i) = (a); (i) < (b); ++(i))
#define RFOR(i,a,b) for(int (i) = (a)-1; (i) >= (b); --(i))
#define CLEAR(a) memset((a),0,sizeof(a))
#define FILL(a,b,l) for(int i=0; i<l; ++i) a[i]= b;
//#define FILL(a,b) memset((a),b,sizeof(a))
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, b, a) for (int i = b; i > a; i--)
#define all(v) v.begin(), v.end()
#define GETCHAR getchar_unlocked
#define pi(n) printf("%d\n",n)
#define pll(n) printf("%lld\n",n)
#define rk() int t; scanf("%d",&t); while(t--)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef long l;
typedef pair<int,int> pii;
typedef vector<int> vec;
typedef vector<pii> vpii;

ll absolutecheck(ll a)
{ if(a < 0) return (a*-1); 
  else return a;
}

int main(){
	
	ll N, maxA=0, maxB=0;
	int a[1000000],b[1000000];
	cin>>N;
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	LFOR(i,0,N)
		cin>>a[i];
	
	LFOR(i,0,N)
		cin>>b[i];

	LFOR(i,1,N)
	{
		ll temp = a[i] - a[i-1];
		//cout << a[i] << " " << a[i-1] << " " << temp << endl;
		if(temp > maxA)
			maxA= temp;
	}
	
	LFOR(i,1,N)
	{
		ll temp = absolutecheck(b[i] - b[i-1]);
		if(temp > maxB)
			maxB= temp;
	}
	//cout << maxA << " " << maxB;
	//return 0;
	if ( maxA > maxB)
		cout<<"Dom"<<endl<<maxA;
	else if( maxB > maxA)
		cout << "Brian" << endl<< maxB;
	else
		cout << "Tie" << endl << maxA;
	return 0;
}
