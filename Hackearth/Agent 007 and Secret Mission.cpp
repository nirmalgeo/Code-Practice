#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<b;i++)
using namespace std;
int sum(int n)
{
	int s=0;
	for(int i=1;i<=n;i++)
	s+=i;

	return s;
}

int main()
{
	int t,n;
	cin>>t;
	string s;
	while(t--)
	{
		cin>>s;
		cin>>n;
		char checkString='0';
		if(sum(n)%2 == 0)
			checkString='1';
		int count=0;
		FOR(i,0,s.length())
		{
			if(s.at(i) == checkString)
				count++;
		}
		cout<<count<<"\n";
	}
	return 0;
}