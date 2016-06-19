#include<bits/stdc++.h>
using namespace std;
inline string anagramword(string a){

	for(int i=0; i<a.length(); i++){
		a[i] = tolower(a[i]);
	}
	sort(a.begin(), a.end());
	return a;
}
int main(){
	vector<string> words;
	map<string, int> m;
	while(1){
		string in;
		cin >> in;
		if(in == "#") break;
		
		words.push_back(in);
		m[anagramword(in)]++;
	}

	sort(words.begin(), words.end());
	for(auto &c: words)
		if(m[anagramword(c)] == 1)
			cout << c << "\n";


	return 0;
}