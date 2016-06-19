#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	int n;
	
	while(t--) {
		cin >> n;
		
		long long arr[16];
		
		for(int i=0; i<n; i++)
			cin >> arr[i];
		
		long long p = 0;
		long long len = 0;
		
		for (int i = 0; i < (1 << n); i++) { 
			long long xorVal = 0, andVal = 1;
			long long count = 0;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)){
					xorVal^= arr[j];
					andVal&= arr[j];
					count++;
				}
			}	
			long long orVal = xorVal | andVal;
			if(orVal > p)	{ p = orVal; len = count; }
			else if(orVal == p && count >  len) { len = count; } 
			
		}
		cout << p << " " << len << "\n";
	}

	return 0;
}