#include<bits/stdc++.h>
#define inf 100005
using namespace std;
int main()
{
	int t;
	long long n,arr[inf];
	cin>>t;
	while(t--)
	{
		cin>>n;
		bool found=false;
		vector<long long> v;
		long long j=0;
		for(long long i=1;i<=n;i++)
		{
			cin>>arr[i];
			if(i==1 || i == v[j])
			{
				v.push_back(arr[i]);
				j++;
			}
		}
		for(auto &c: v)
		{
			cout << c << " " ;
		}
		
		if(found)
			cout<<"YES\n";
		else
			cout<<"NO\n";
		
	}
	return 0;
}
