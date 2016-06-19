#include<bits/stdc++.h>
using namespace std;
int city[100000];

int main()
{
	int n,k;
	cin>>n>>k;
	for (int i=0;i<n;i++)
		city[i] = i;
	
	int a,b;
	while(k--)
	{
		cin>>a>>b;
		city[b] = a;
	}
	
	int count =0;
	for(int i=0;i <n;i++)
		if(city[i] == i)
			count++;
			
	cout<<count;


	return 0;
}