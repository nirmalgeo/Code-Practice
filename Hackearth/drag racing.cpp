#include<bits/stdc++.h>
using namespace std;
int main()
{
	vector<pair<string,int>> v;
	
	int n;
	cin>>n;
	int k= pow(2,n);
	
	while(k-1)
	{
		string winner, loser;
		cin>>winner >> loser;
		for(auto &c: v)
		{
			if(c.first == loser)
				c.second = 0;
		}
		
		v.push_back(make_pair(winner, 1));
	}
	
	string finalwinner;
	for(auto &c: v)
		{
			if(c.second == 1)
				finalwinner = c.first;
		}
		
	cout<< finalwinner;
	
	return 0;
}