#include<bits/stdc++.h>
using namespace std;
int main(){

	int n;
	cin >> n;
	vector<string> v;
	while(n--){
		string s;
		cin >> s;
		v.push_back(s);
	
	}
	
	sort(v.begin(), v.end());
	vector<string> output;

	do{
		string s;
		for(auto &c: v)
			s+=c;
		output.push_back(s);
	}while(next_permutation(v.begin(), v.end()));

	
	
	sort(output.begin(), output.end());
	
/*	
	for(auto &c: output)
		cout << c << "\n";
	*/
	
	cout << output[0];

	return 0;
}