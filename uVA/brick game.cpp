#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int tt=1; tt<=t; tt++){
		int n;
		scanf("%d", &n);
		vector<int> v;
		v.resize(n);
		for(int i=0; i<n; i++)
			cin>>v[i];
		
		sort(v.begin(), v.end());
		
		printf("Case %d: %d\n",tt, v[n/2]);
	}

	return 0;
}