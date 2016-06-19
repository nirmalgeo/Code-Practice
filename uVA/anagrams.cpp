// uva 454
#include<bits/stdc++.h>
using namespace std;

inline string generateanagram(string a){
	string temp = "";
	for(int i=0;i<a.length(); i++)
		if(a[i] != ' ')
			temp += a[i];
			
	sort(temp.begin(), temp.end());
	return temp;
}

int main(){
	int t;
	string line;
	scanf("%d", &t);
	getline(cin, line);
	getline(cin, line);
	while(t--){

		vector<string> v;
		map<string, string> m;
		while(getline(cin, line), line!= ""){
			v.push_back(line);
			m[line] = generateanagram(line);
		}
		
		sort(v.begin(), v.end());
		for(int i=0; i < v.size(); i++)
			for(int j=i+1; j < v.size() ; j++)
				if(m[v[i]] == m[v[j]])
					cout << v[i] << " = " << v[j] <<"\n";
		
		if(t)
		cout <<"\n";
	}

	return 0;
}