s#include<bits/stdc++.h>
#define INF 1000003
using namespace std;
int main()
{
	int t,n;
	int a,b;
	int AVal[INF];
	
	
	cin >> t;
	
	while(t--)
	{
		int count =0;
		cin>>n;
		memset(AVal, 0, sizeof(AVal));
		
		for(int i=0;i < n ;i++)
		{
			cin >>  a >> b ;
			
			AVal[a]++;
			if(!AVal[b])
				count++;
			else
				AVal[b]--;
			
		}
		
		cout << count << "\n";
	}




	return 0;
}
