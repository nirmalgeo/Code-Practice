#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin >> t;
	while(t--){
	
		string s;
		cin >> s;
		
		int vC = 0, cC = 0;
		int cnt = 0;
		bool hard = false;
		
		for(int i=0;i < s.length(); i++){
			if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i'  || s[i] == 'o'  || s[i] == 'u' || s[i] == 'y' ){
				cnt = 0;
				vC++;
			}
			else {
				cnt++;
				cC++;
			}
			
			if(cnt == 3) { hard = true; break; }
		}
	
		if(hard) cout << "hard\n";
		else{
			if(cC > vC)
				cout << "hard\n";
			else
				cout << "easy\n";
		}
	
	}



	return 0;
}