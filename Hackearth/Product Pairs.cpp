#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,k,count=0;
	cin>>n>>k;
	n--;
	
	while(n--)
	{
		long long a,b;
		cin>> a >> b;
		if( a*b <= k)
			count++;
	}
	
	cout <<count;

	return 0;
	
}