#include<bits/stdc++.h>
using namespace std;
int main()
{
	string line;
	while(getline(cin, line))
	{
		string temp;
		vector<string> v;
		for(int i=0;i<line.length();i++)
		{
			if(line[i] == ' ')
			{
				reverse(temp.begin(), temp.end());
				v.push_back(temp);
				temp = "";
				v.push_back(" ");
			}
			else
				temp = temp + line[i];
		}
		
		reverse(temp.begin(), temp.end());
		v.push_back(temp);
		temp = "";
		
		for(auto &c: v)
			cout << c;
		cout << "\n";

	}
	
	return 0;
}