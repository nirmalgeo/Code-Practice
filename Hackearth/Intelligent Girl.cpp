#include<bits/stdc++.h>
using namespace std;
int Hash[10005];
int main()
{
	string s;
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		if(s.at(i) == '2' || s.at(i) == '4' || s.at(i) == '6' || s.at(i) == '8')
			Hash[i] = 1;
	}

	for(int i=0;i< s.length(); i++)
	{
		for(int j=i+1; j <s.length(); j++)
			Hash[i] = Hash[i] + Hash[j];
	}
	
	
	for(int i=0;i< s.length(); i++)
		cout<<Hash[i]<< " ";


	return 0;
}