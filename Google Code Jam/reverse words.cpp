//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("B-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	cin.ignore();
	for(int tt =1; tt <= cases; tt++){
// code starts here 
		string str;
		getline(cin,str);
		vector<string> v;
		string temp = "";
		for(int i=0; i<str.length(); i++){
			if(str[i] != ' '){
				temp += str[i];
			}
			else { v.push_back(temp); temp = "";}
		}
		v.push_back(temp);
		
		reverse(v.begin(), v.end());

// code ends here 

		cout << "Case #"<< tt << ": ";
		auto it = v.begin();
		for(auto &c: v) {
			cout << c;
			it++;
			if(it != v.end()) cout << " ";
		}
		cout << "\n";


	}

	return 0;
}