#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, t;
	cin>> n >> t;
	assert(n>=1 && n<=100);
	assert(t>=2 && t<=10);
	
	int val = 1;
	
	if(t >=2 && t<=9)
	{
		
		while(--n)
		{
			val = val * 10 + 1;
		}
	
		val = val *t;
		
		if( val%t == 0)
			cout << val;
		else
			cout << -1;
	}
	else
	{
		cout << pow(10,n);
	
	}
	
	return 0;
}