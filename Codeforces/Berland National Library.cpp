#include<iostream>
#include<stdio.h>
#define INF 100005
using namespace std;
bool a[INF];
int main()
{
	int n,b;
	cin>>n;
	char c, flag;
	int count = 0;
	for(int i=0;i<n;i++)
	{
		char ch = getchar();
		while(ch != '\n')
			cin>>flag;
		cin>>c;
		cin>>b;

		if(!a[b])
			count++;			
		
		a[b] = true;
	}
	cout <<count;



	return 0;
}