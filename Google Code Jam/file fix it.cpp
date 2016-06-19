//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int n,m, ans=0;
		cin >> n >> m;
		
		set<string> dirs;
		string s;
		while(n--){
			cin >>  s;
			string temp = "";
			for(int i=1; i<s.length(); i++)
				if(s[i+1] == '/' || i == s.length()-1){
					temp = s.substr(0,i+1);
					dirs.insert(temp);
				}
		}
		
		while(m--){
			cin >>  s;
			string temp = "";
			for(int i=1; i<s.length(); i++)
				if(s[i+1] == '/' || i == s.length()-1){
					temp = s.substr(0,i+1);
					if(dirs.find(temp) == dirs.end()) {	ans++; dirs.insert(temp); }
				}
		}
		

// code ends here 

	cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}