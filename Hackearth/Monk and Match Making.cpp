#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	int q;
	int l1,r1,l2,r2;
	while(q--)
	{
		cin>>l1>>r1>>l2>>r2;
		int k=s.length();
		if( s.substr(l1-1, k-r1) == s.substr(l2-1, k-r2))
			cout<<"YES"<<"\n";
		else 
			cout<<"NO"<<"\n";
	
	}


	return 0;
}