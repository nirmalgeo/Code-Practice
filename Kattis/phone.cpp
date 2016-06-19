#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	for(int tt=1;tt<=t;tt++){
		int n;
		scanf("%d ", &n);
		vector<string> v;
		long long x;
		string findVal = "YES";
		for(int qq=1; qq<=n;qq++){
			string x;
			cin>>x;
			v.push_back(x);
		}
		sort(v.begin(), v.end());
		int count =0;
		for(int idx=1;idx<n;idx++){
			string s1= v[idx], s2 =v[idx-1];
			if(s1.find(s2) != string::npos){
				findVal="NO";
				break;
			}
		}
		
		cout << findVal << endl;
	}
	return 0;
}