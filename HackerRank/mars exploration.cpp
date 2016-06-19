#include<bits/stdc++.h>
using namespace std;
int main(){

	string s;
	cin>>s;
	int count = 0;
	for(int i=0; i+3 < s.length(); i+=3)
		
		int j=i;
		if(s[j] != 'S')
			count++;
		if(s[j+1] != 'O')
			count++;
		if(s[j+2] != 'S')
			count++;
	}
	cout << count ;
	


	return 0;
}