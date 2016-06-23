#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,k,l;
	cin>>t;
	unordered_map<string,int> m;
	vector<string> v;
	while(t--)
	{
		cin>>n>>k;
		
		fflush(stdin);
		while(n--)
		{
			string s;
			cin>>s;
			v.push_back(s);
		}
		
		while(k--)
		{
			fflush(stdin);
			cin>>l;
			while(l--)
			{
				string s;
				cin>>s;
				if(m.find(s) == m.end())
					m.insert({s,1});
			}
		}
		
		for(auto &c: v)
		{
			if(m.find(c) != m.end())
				cout << "YES" << " ";
			else
				cout << "NO" << " ";
		}
		cout<<"\n";
		fflush(stdin);
		v.clear();
		m.clear();
	}
	return 0;


}