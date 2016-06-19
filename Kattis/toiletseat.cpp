#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	char prev = s.at(0);
	int first=0;
	int second =0;
	int third=0;
	
	if(s.at(1) != s.at(0))
	{
		first++;
		second++;
		third++;
	}
	
	if(s.at(1) == 'D')
		first++;
	if(s.at(1) == 'U')
		second++;
	
	prev= s.at(1);
	
	
	for(int i=2; i < s.length(); i++)
	{
		/*initial*/
		if(s.at(i) == 'D')
			first+=2;
		if(s.at(i) == 'U')
			second+=2;
			if(prev != s.at(i))
			third++;
	
		prev=s.at(i);
		
	}
	cout<< first<< "\n" << second << "\n" << third;
	return 0;
}