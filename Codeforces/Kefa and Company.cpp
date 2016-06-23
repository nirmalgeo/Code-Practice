#include<bits/stdc++.h>
using namespace std;
long long dp1[100002], dp2[100002];
int main()
{
	long long n,d, m,s;
	vector<pair<long long,long long>> v;
	cin>>n>>d;
	for(int i=0;i<n;i++)
	{
		cin>>m>>s;
		v.push_back(make_pair(m,s));
	}
	
	sort(v.begin(), v.end());

	dp1[0] = v[0].first;
	dp2[0] = v[0].second;
	long long max = dp2[0];
	for(int i=1;i<n;i++)
	{
		if(abs(v[i].first - dp1[i-1]) <= d)
		{
			dp2[i] = dp2[i-1] + v[i].second;
			dp1[i] = abs(v[i].first - dp1[i-1]);
		}
		else
		{
			dp2[i] = v[i].second;
			dp1[i] = v[i].first;
		}
	
		if(dp2[i] > max)
			max = dp2[i];
	}
	
	cout << max;
	return 0;
}