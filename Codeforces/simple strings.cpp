#include<bits/stdc++.h>
using namespace std;
int main(){

	// code starts here
	string s;
	cin >> s;
	
	int dp[200006];

	dp[0] = 1;
	int maxVal = -1;
	int end = 0;
	for(int i=1; i<s.length(); i++){
		if(s[i] == s[i-1])
			dp[i] = dp[i-1]+1;
		else
			dp[i] = 1;
			
		if(dp[i] > maxVal){
			maxVal = dp[i];
			end = i;
		}
	}
	
	int start ;
	for(int i=end; ; i--)
		if(dp[i] == 1){
			start = i;
			break;
		}

	char f='A',b='A';
	
	if(start!=0) f= s[start-1];
	if(end != s.length()-1) b = s[end+1];
	
	char ch = 'A';
	
	if(f>=b) ch = f + 1;
	else ch = b + 1 ;
	
	for(int i=start; i<end; i+=2)
		s[i]= ch;
	
		
	cout << s ;
	// code ends here 
	return 0;
}