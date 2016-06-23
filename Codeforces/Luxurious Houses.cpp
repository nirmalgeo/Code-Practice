#include<bits/stdc++.h>
#define INF 100006
long long dp[INF];
using namespace std;
int main()
{
	long long n;
	cin>> n;
	long long a[INF];
	for(long long i=0;i<n;i++)
	{
		cin >> a[i];
	}
	
	dp[n-1] = a[n-1];
	
	for(long long i=n-2;i>=0; i--)
	{	
		if(a[i] > dp[i+1])
			dp[i] = a[i];
		else
			dp[i] = dp[i+1];
	}
	
	for(long long i=0; i<n;i++)
	{
		if(a[i] == dp[i])
			cout << 0 << " ";
		else
			cout << abs( a[i] - dp[i]) + 1 << " ";
	}


	return 0;
}