#include<bits/stdc++.h>
using namespace std;


class ExactTreeEasy{
	vector <int> getTree(int n, int m)
	{	
		vector<int> v;
		v.push_back(0);
		v.push_back(1);
		m--;
		for(int i=2;i<n;i++)
		{
			v.push_back(1);
			v.push_back(i+1);
			m--;
			if(m == 1 || m==0)
				break;
		}
		
		for(auto &c: v)
			cout << c << " ";
	
	}
};