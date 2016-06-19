#include<bits/stdc++.h>
using namespace std;
string in;
int q;

long long arr[26];

void generateData(){
	char ch = '\0';
	long long val = 0;
	string temp = "";
	bool copyCheck = false;
	for(int i=0; i< in.length(); i++){
		if(in[i] >= 97 && in[i] <= 122)  { 
			// copy values 
			if(copyCheck) { arr[ch - 97] += stoi(temp); }
			ch = in[i];
			temp = "";
		}
		
		else {
			temp += in[i];
			copyCheck = true;
		}
	}
	
	// copy last value
	arr[ch - 97] +=  stoi(temp); ;
}

/*
void printVal () {
	
	for(int i=0; i<26 ;i++ )
		cout << (char) i+97 << " " << arr[i] <<"\n";
}
*/

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> in;
	generateData();
	//printVal();
	return 0;
	cin >> q;
	
	while(q--){
		long long k, sum = 0;
		cin >> k;
		
		for(int i=0; i< 26; i++){
			sum += arr[i];
			if(sum >= k) {
				cout << (char) (i + 97) <<"\n";
				break;
			}
		}
	}

	return 0;
}