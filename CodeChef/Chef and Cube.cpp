#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	string s[6];
	vector<string> v;
	cin>>t;
	for(int tt=0; tt<t; tt++)
	{
		for(int j=0;j<6;j++)
			cin>>s[j];
		
		bool flag = false;
	
		for(int j=0;j<6;j++)
		{
			if(j%2==0)
			{
				if( s[j] == s[(j+2)%6] || s[j] == s[(j+3)%6] )
				{
					if(s[j] == s[(j+4)%6] ||  s[j] == s[(j+5)%6])
					{
						flag = true;
						break;
					}
				}			
			}
			else
			{
			
				if( s[j] == s[(j+1)%6] || s[j] == s[(j+2)%6] )
				{
					if(s[j] == s[(j+3)%6] ||  s[j] == s[(j+4)%6])
					{
						flag = true;
						break;
					}
				}			
			}	
		}
		
		if ( flag )
			v.push_back("YES");
			
		else
			v.push_back("NO");
		
	}
	
	for(auto &c: v)
		cout << c << endl;


	return 0;
}