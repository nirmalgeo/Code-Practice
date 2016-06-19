//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (long long)1e18
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
typedef long long ll;


map<char, int> m;
map<char, string> fullwords;

vector<int> ans;
string s;


string replaceWords(string s){
	for(int i=0; i< s.length(); i++){
		if(m.find(s[i]) != m.end()){
			string temp = fullwords[s[i]];
			int num = m[s[i]];
			for(int j=0; j<temp.length(); j++){
				auto it = find(s.begin(), s.end(), temp[j]);
				*it = '+';
			}
			ans.push_back(num);
		}
	}
	return s;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	
	for(int cas =1; cas <= cases; cas++){
	
// code starts here 

		m['Z'] = 0; fullwords['Z'] = "ZERO";
		m['W'] = 2; fullwords['W'] = "TWO";
		m['U'] = 4; fullwords['U'] = "FOUR";
		m['X'] = 6; fullwords['X'] = "SIX";
		m['G'] = 8; fullwords['G'] = "EIGHT";
		
		string s;
		
		cin >> s;
		
		s= replaceWords(s);
		
		m.clear(); 
		fullwords.clear();
	
		m['F'] = 5; fullwords['F'] = "FIVE";
		m['O'] = 1; fullwords['O'] = "ONE";
		m['H'] = 3; fullwords['H'] = "THREE";
		
		
		
		s= replaceWords(s);
		
	
		
		m.clear();
		fullwords.clear();
		
		m['I'] = 9; fullwords['I'] = "NINE";
		m['V'] = 7; fullwords['V'] = "SEVEN";
		s = replaceWords(s);
	
		
// code ends here 

		sort(ans.begin(), ans.end());
		
		cerr << "test " << cas << " done" << endl;

		cout << "Case #"<< cas << ": ";
		for(auto &c: ans) cout << c;
		cout << "\n";

		m.clear();
		fullwords.clear();
		ans.clear();
	}

	return 0;
}