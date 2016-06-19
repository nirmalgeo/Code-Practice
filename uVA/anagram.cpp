// uva 195
#include<bits/stdc++.h>
using namespace std;
map<int , char> m;
inline void generatehashTable(){
	char ch;
	int d;
	for(int i=65; i<=90; i++){
		ch = i;
		d = 2*i;
		m.insert({d, ch});
	}
	
	for(int i=97; i<=122; i++){
		ch = i;
		d = 131 + 2*(i - 97);
		m.insert({d, ch});
	}
}


int main(){
	int n;
	scanf("%d", &n);
	generatehashTable();

	while(n--){
		string s;
		cin>> s;

		vector<int> a;
		int cnt=0, d;
		for(int i=0; i<s.length(); i++){
			int d= s[i];
			if ( d>=65 && d<=90) d=d*2;
			else d = 131+ 2*(d-97);
			
			a.push_back(d);
		}
		
		sort(a.begin(), a.end());
		
		
		int n = a.size();
		do{
			for(int i=0; i<n; i++)
				cout << m[a[i]];
			cout << "\n";
	
		}while(next_permutation(a.begin(), a.end()));
	}
	return 0;
}