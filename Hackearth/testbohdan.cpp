/*
*/
 
//#pragma comment(linker, "/STACK:16777216")
#include <fstream>
#include <iostream>
#include <string>
#include <complex>
#include <math.h>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <stdio.h>
#include <stack>
#include <algorithm>
#include <list>
#include <ctime>
#include <memory.h>
#include <ctime> 
 
#define y0 sdkfaslhagaklsldk
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define tm sdfjahlfasfh
#define lr asgasgash
 
#define eps 1e-9
#define M_PI 3.141592653589793
#define bs 99991
#define bsize 256
 
using namespace std;

int tests,t[1<<20],ar[1<<20],ans[1<<20],n;

int sum(int x)
{
	int res=0;
	for (;x>=0;x=(x&(x+1))-1)
	{
		res+=t[x];
		cout << x<< " " << t[x] << "\n";
	}
	return res;
}
void inc(int i,int delta)
{
	for (;i<=1000000;i=(i|(i+1)))
	{
		t[i]+=delta;
		cout << i << " " << t[i] << "\n";
	}
}

int main(){
//freopen("newlines.in","r",stdin);
//freopen("newlines.out","w",stdout);
//freopen("F:/in.txt","r",stdin);
//freopen("F:/output.txt","w",stdout);
ios_base::sync_with_stdio(0);
//cin.tie(0);

cin>>tests;
for (;tests;--tests)
{
	cin>>n;
	for (int i=0;i<=1000000;i++)
		t[i]=0;
	for (int i=0;i<n;i++)
	 cin>>ar[i];
	for (int i=n-1;i+1;--i)
	{
		cout << "\n SUM:\n";
		ans[i]=sum(ar[i]-1);
		cout << "\n RETURN:\n";
		cout << i << " " << ans[i] << "\n";
		cout << "\n INC:\n";
		inc(ar[i],1);
	}
	for (int i=0;i<n;i++)
	{
		if (i)cout<<" ";
		cout<<ans[i];
	}
	cout<<endl;
}
//cin.get();cin.get();
return 0;}   