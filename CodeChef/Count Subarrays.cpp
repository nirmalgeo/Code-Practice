#include<bits/stdc++.h>
#define INF 1000000000
//int arr[INF];-
using namespace std;
int main()
{
	int n,temp;
	vector<int> v, dp;
	int t;
	cin>>t;
	while(t--)
	{
		cin >> n;
		cin >> temp;
		v.push_back(temp);
		int prev = temp;
		int count=1;
		
		for(int i=1;i<n;i++)
		{
			cin>>temp;

			if( temp >= prev)
			{
				count++;
			}
			else
			{
				dp.push_back(count);
				count = 1;
			}		
			prev = temp;
			//v.push_back(temp);
		}
		dp.push_back(count);
		long long val = 0;
		for(auto c : dp)
		{
			cout << c << " ";
			
		}
		cout << val << "\n";
	
	}
	
	return 0;

}