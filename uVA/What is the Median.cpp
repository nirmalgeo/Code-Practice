// uva 10107
#include<bits/stdc++.h>
using namespace std;
vector<long long> v;
int main(){
	long long n;
	while(scanf("%d", &n)  != EOF){
		v.push_back(n);
		sort(v.begin(), v.end());
		int n = v.size();

		if(n%2==1){
			printf("%d\n",v[n/2] );
		}
		else{
			int mid = v[n/ 2] + v[n/2 - 1];
			mid/=2;
			printf("%d\n", mid);
		}
	}

	return 0;
}