#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<b;i++)
using namespace std;
int main()
{

	string keys[]= {" ", "", "abc", "def", "ghi","jkl","mno","pqrs","tuv","wxyz"};
	int n;	
	cin>>n;
	
	FOR(tt,0,n)
	{
		string s;
		cin.ignore();
		getline(cin,s);
		cout<<"Case #"<<tt+1<<": ";
		int last=-1;
		
		FOR(i,0, s.length())
		{
			
			int len = sizeof(keys)/ sizeof(keys[0]);
			
			FOR(j,0, len)
			{
				FOR(k,0, keys[j].length())
				{
					if(keys[j][k] == s[i])
					{	
						k++;
						if(last == j and last!=0)
							cout << " ";
							
						last = j;
						
						while(k--)
						{
							cout << j;
						}
						break;
					}
				}
			}
		
		}

	}


	return 0;
}