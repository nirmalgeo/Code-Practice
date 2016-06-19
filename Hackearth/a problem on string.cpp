#include<bits/stdc++.h>
using namespace std;
int main(){

	int n;
	cin >> n;
	string s;
	cin >> s;
	
	map<char, int> m;
	
	for(int i=0; i<n; i++)
		m[s[i]]++;
		
	int q;
	cin >> q;
	while(q--){
		char X, Y;
		cin >> X >> Y;
		cout << m[X] * m[Y] << "\n";
		
	}

	return 0;
}