#include<bits/stdc++.h>
typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;

using namespace std;

int main(){
	int test;
	cin>>test;
	while(test--){
		string s;
		int n;
		cin>>s;
		cin>>n;
		sort(s.begin(),s.end());
		while(n--){
			next_permutation(s.begin(),s.end());
		}
		cout << s << "\n";
	
	}
	
	return 0;
}