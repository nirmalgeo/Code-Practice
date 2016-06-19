#include<bits/stdc++.h>
using namespace std;
int main()
{
	string t;
	cin>>t;
	char c = t.at(8);
	char first = t.at(0);
	char second = t.at(1);
	int num = (first - 48) *10 + ( second -48);
	cout << setw(2) << setfill('0') <<  num ;
	if(c=='P')
		num = (num + 12)%24;
		
	if( num < 13)	
		c = 'A';
	
	t.at(8) = c;
	
	string temp = to_string(num);
	t.at(0) = temp.at(0);
	t.at(1) = temp.at(1);
	
	t.replace(t.end()-2, t.end(), "");
	cout << t;
	
		


	return 0;
}