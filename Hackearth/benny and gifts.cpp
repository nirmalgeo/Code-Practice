#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	
	cin >> s;
	
	map<pair<int,int>,bool> m;
	
	m[{0,0}] = true;
	
	int x= 0, y=0;
	int count = 0;
	for(int i=0; i< s.length(); i++){
		if(s[i] == 'R')  y++;
		else if(s[i] == 'L') y--;
		else if(s[i] == 'D') x++;
		else if(s[i] == 'U') x--;
		
		if(m[{x,y}])  count++;
		else m[{x,y}] = true;
	}

	cout << count;
	return 0;
}