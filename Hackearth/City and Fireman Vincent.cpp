#include<bits/stc++.h>
#define INF 1000000007
using namespace std;
int main()
{
	int city[1001];
	int minRisk[1001];
	int risk[1001];
	
	int n,k,a,b;
	
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>> risk[i];
		city[i] = i;
	}
	
	cin>>k;	
	while(k--)
	{
		cin>>a>>b;
		if(a<=b)
			city[b] = a;
		else
			city[a] = b;
	}
	
	
	
	





	return 0;
}