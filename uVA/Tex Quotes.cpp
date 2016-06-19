#include<bits/stdc++.h>
using namespace std;
int main()
{
	string line;
	bool left= false;
	
	while( getline(cin,line))
	{
		list<char> text;
		list<char>::iterator it=text.begin();
		for(int i=0;i<line.length();i++)
		{
			if(line[i] == '"' && !left)
			{
				left = true;
				text.insert(it,'`');
				text.insert(it,'`');
			}
			else if(line[i] == '"' && left)
			{
				text.insert(it, '\'');
				text.insert(it, '\'');
				left = false;
			
			}
				
			else
				text.insert(it, line[i]);
			
		}
		for(auto &c: text)
			cout << c;
		cout << "\n";
	}
	

	return 0;
}