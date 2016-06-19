/*logic ------------
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define FOR(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define RFOR(i,a,b) for(int (i) = (a)-1; (i) >= (b); --(i))


using namespace std;


int main()
{
	int t;
	string s;
	vector<string> v;
	cin >> t;
	FOR(i,0,t)
	{
		cin >> s;
		std::reverse( s.begin(), s.end());
		cout << s;
	}
	return 0;
}
	
	

