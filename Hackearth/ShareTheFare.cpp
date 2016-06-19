#include<bits/stdc++.h>
using namespace std;
map<string, long long> m;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n,q;
		scanf("%d %d", &n, &q);
		string s;
		for(int i=0; i<n; i++){
			cin>>s;
			m.insert({s,0});
		}
		for(int i=0; i<q; i++){
			cin>>s;
			int money;
			scanf("%d", &money);
			int num;
			scanf("%d", &num);
			map<string,long long> ::iterator it = m.find(s);
			int val = money/ (num+1);
			int rem = money% (num+1);
			int amount = money - (val+rem);
			it->second = it->second + amount;
			for(int i=0; i<num; i++){
				string name;
				cin>>name;
				it = m.find(name);
				it->second = it->second - val;
			}
		}
		
		for(auto &c : m){
			if(c.second < 0){
				cout << c.first << " owes " << -1*c.second <<"\n";
			}
			
			else if(c.second == 0){
				cout << c.first << " neither owes nor is owed\n";
			}
			
			else {
				cout << c.first << " is owed " << c.second <<"\n";
			}
		
		}
	
	
		m.clear();
	}


	return 0;
}