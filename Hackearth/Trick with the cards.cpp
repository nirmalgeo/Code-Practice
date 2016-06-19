#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	long long n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout << (n / 3) + (n % 3 > 0);  << "\n";
	}
	
	return 0;
}