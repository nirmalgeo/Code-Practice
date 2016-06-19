#include<bits/stdc++.h>
#define INF 2000000000
using namespace std;
int main()
{
	int m,n;
	map<string,long long> hash;
	long long weight;
	string word;
	cin >> m >> n;
	while(m--)
	{
		scanf(" ");
		cin >> word >> weight;
		assert(word.length()<=16);
		assert(weight>=0 && weight<=1000000);
		if(hash.find("word") == hash.end())
			hash.insert(make_pair(word,weight));
	
	}
	
	
	for(int i=0; i < n ; i++)
	{
		long long value=0;
		string line;
		scanf(" ");
		while(getline(cin, line))
		{
			if(line == ".")
				break;
			
			string temp = "";
			map<string,long long>::iterator it;
			for(int i=0;i< line.size(); i++)
			{
				if( line[i]  == ' ')
				{
					it = hash.find(temp);
					if(it != hash.end())
						value += it->second;
					temp = "";
				}
				else
					temp = temp + line[i];
			}
			
			it = hash.find(temp);
			if(it!= hash.end())
				value += it->second;
		}
		
		cout << value%INF << "\n";
	}
	return 0;
}