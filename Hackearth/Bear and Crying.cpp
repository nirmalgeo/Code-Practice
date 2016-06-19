#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
int main()
{
	long long n;
	string line;
	getline(cin, line);
	list<char> perm;
	list<char>::iterator it = perm.begin();
	for(long long i=0; i < line.size();i++)
	{
		perm.insert(it,line[i]);
		it++;
	}
	
	long long count = 0;

	do {
	bool first = false;
	bool second = false;
	bool mid = false;
	for(auto &c: perm)
	{
		if( c == ';' && first == false)
			first = true;
		else if ( c == '_' && first == true)
			mid = true;
		else if( c == ';' && first == true && mid == true)
		{
			count++;
			break;
		}
	}
	} while (next_permutation(perm.begin(), perm.end()));
	
	cout << count %INF;

	return 0;
}