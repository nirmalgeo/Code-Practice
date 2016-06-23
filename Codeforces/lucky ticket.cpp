#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	
	bool check =true;
	
	for(int i=0; i< s.length(); i++){
		if(s[i] != '4' && s[i] != '7'){
			check = false;
			break;
		}
	}
	
		
	if(check){
		int front = 0 , back = 0;
		
		for(int i=0; i<n/2; i++){
			front += (s[i] - '0');
		}
		for(int i=n/2; i<n; i++){
			back += (s[i] - '0');
		}
		//cerr << front << " " << back << "\n";
		
		if(front == back)
			cout << "YES";
		else
			cout << "NO";
	
	}
	else
		cout << "NO";
		
	return 0;
}