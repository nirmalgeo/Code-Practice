//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (int)1e4+1
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int n, ans = 0;
		cin >> n;
		
		int A[n], B[n];
		
		for(int i=0; i<n; i++) cin >> A[i] >> B[i];
		// let's say the x = 1 and x=2 for A and B respectively
		
		for(int i=0; i<n; i++)
			for(int j=0; j<i; j++)
				if( (A[i] > A[j]) != (B[i] > B[j]))
					ans++;
				
		
// code ends here 

	cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}