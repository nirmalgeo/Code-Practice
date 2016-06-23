#include<bits/stdc++.h>
using namespace std;
int main(){

	string s, ans = "";
	cin >> s;
	
	for(int i=0; i< s.length(); i++){
		if(s[i] < 'a')
			s[i] += 32;
		
		if(!(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] =='y'))
			ans = ans + "." + s[i];
	}
	cout << ans ;

	return 0;
}