#include<bits/stdc++.h>
using namespace std;
int dp[100002];
int main()
{
	long long n,arr[100002];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	
	dp[0] = 1;
	int max = 1;
	for(int i=1;i<n;i++)
	{
		if(arr[i] >= arr[i-1])
			dp[i] = dp[i-1] + 1;
		
		else
			dp[i] = 1;
		
		if(dp[i] > max)
			max = dp[i];
	}

	cout << max;

	return 0;
}