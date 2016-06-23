#include<bits/stdc++.h>
#define MAX (int)1e5+5
using namespace std;
long long arr[MAX], E[MAX], J[MAX];
int main(){
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		
		for(int i=0; i<n; i++) cin >> arr[i];
		
		long long curMax = 0 , maxx = 0;
		
		curMax = arr[0];
		
		
		
		memset(E, 0 , sizeof E);
		memset(J, 0 , sizeof J);
		
		for(int i=1; i<n; i++){
			curMax = max(arr[i] , arr[i] + curMax);
			maxx = max(curMax , maxx);
		}
		
		
		
		
	
	
	}

	return 0;
}