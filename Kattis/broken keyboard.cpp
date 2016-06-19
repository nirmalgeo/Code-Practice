#include<bits/stdc++.h>
using namespace std;
int main()
{
	string line;
	
	while(getline(cin,line))
	{
	
	list<char> beijutext;
	list<char>::iterator it = beijutext.begin();
	for(int i=0; i<line.length();i++)
	{
		if(line.at(i) == '[')
			it= beijutext.begin();
		else if(line.at(i) == ']')
			it= beijutext.end();
		else
		{
			//cout<< line[i] << "\n";
			beijutext.insert(it, line[i]);
			
		}
	}

	for(auto &c: beijutext)
		cout <<c;
	
		cout<<"\n";
	}



	return 0;
}