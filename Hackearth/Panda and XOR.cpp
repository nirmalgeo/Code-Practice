#include<bits/stdc++.h>
#define INF 1000000007
int freq[100001];
int arr[100001];
using namespace std;
int main()
{
	int n;
	
	cin >>n ;
	for(int i=0;i<n;i++)
		cin>>arr[i];
		
	for (int subset = 0; subset < (1 << n); subset++) {
	int x = 0;
	for (int i = 0; i < n; i++) {
	if ((subset & (1 << i)) != 0) {
		x = x ^ arr[i];
		//cout << arr[i] << "  ";
	}
	}
	freq[x]++;
	//cout <<  x ;
	//printf("\n");
	}
	
	long long count = 0;
	for (int i = 1;i <= 128;i++)
	{
		long long val = ( freq[i] * (freq[i]-1))/ 2;
		count += val;
	}
	cout << count%INF << "\n";

	return 0;
}