#include<bits/stdc++.h>
using namespace std;
int a[10];
int main()
{
	int t,n,x;
	cin>>t;
	while(t--)
	{
		cin>>n;
		memset(a,0,sizeof(a));
		int count =0;
		for(int i=0;i <n; i++)
		{
			cin>>x;
			if(a[x%10])
				count++;
		}
		cout <<count;
	}

	return 0;
}