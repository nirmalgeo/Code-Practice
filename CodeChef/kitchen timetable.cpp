#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		
		int n;
		scanf("%d", &n);
		
		long long A[n], B[n], C[n];
		int count = 0;
		for(int i=0; i<n; i++){
			cin >> A[i];
		}
		for(int i=0; i<n; i++){
			cin >> B[i];
			
			if(i==0) C[i] = B[i];
			else { C[i] = A[i-1] + B[i]; }
			if( C[i] <= A[i]) count++;
			//cout << C[i] << "\n";
		}
		
		cout << count << "\n";
	
	}

	return 0;
}