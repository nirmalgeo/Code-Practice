#include<bits/stdc++.h>
using namespace std;
string u[100000];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		scanf(" ");
		string line;
		getline(cin,line);

		istringstream stream(line);
		int a;
		vector<int> v;
		while(stream>>a)
		{
			v.push_back(a);
		}
		scanf(" ");
		getline(cin,line);
		
		string temp="";
		int n=0;
		for(int i=0; i< line.size(); i++)
		{
			if(line[i] == ' ')
			{
				u[v[n++]] = temp;
				temp = "";
				continue;
			}
			temp = temp + line[i];
		}
		u[v[n++]] = temp;
		
		for(int i=1;i<=n;i++)
			cout<<u[i]<<"\n";
		cout<<"\n";
	}
	return 0;
}