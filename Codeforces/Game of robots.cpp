#include<bits/stdc++.h>
#define inf (long long)(1e6 +5)
using namespace std;
long long arr[inf];

int main(){
	
	long long n, k, id;
	
	cin >> n >> k;
		
	for(int i=1; i<=n; i++) 
		cin >> arr[i];
	
	vector<long long> v;
	v.resize(n+1);
	v[0] = 0;
	v[1] = 1;
	
	for(int i=2; i<=n; i++)
		v[i] = v[i-1] + i;
		
	for(int i=1; i<=n; i++){
		if(v[i] >=k ){
			cout << arr[k- v[i-1]] << "\n";
			break;
		}
	}
	
	
	return 0;
}