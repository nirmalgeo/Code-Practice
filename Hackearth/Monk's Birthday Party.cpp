#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n;
	scanf("%d",&t);
	
	while(t--){
		scanf("%d ",&n);
		set<string> se;
		while(n--){
			string s;
			getline(cin,s);
			se.insert(s);
		}
			
		for(auto &c: se)
			cout<<c<<"\n";
	
	
	}
	return 0;
}