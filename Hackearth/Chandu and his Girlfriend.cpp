#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		vector<long long> v;
		while(n--){
			long long a;
			scanf("%lld",&a);
			v.push_back(a);
		}
		sort(v.rbegin(), v.rend());
		
		for(auto &c: v)
			cout<<c<< " ";
		cout << "\n";
	}
	return 0;
}