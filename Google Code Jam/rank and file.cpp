//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (long long)1e18
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
typedef long long ll;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("B-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int n, temp;
		cin >> n;
		int arr[2501];
		memset(arr, 0 , sizeof arr);
		
		for(int i=0; i<(2*n-1); i++) {
			for(int j=0; j<n; j++){
				cin >> temp;
				arr[temp]++;
			}
		}
		
		
		
// code ends here 

	
		cerr << "test " << cas << " done" << endl;

		cout << "Case #"<< cas << ": ";
		for(int i=1; i < 2501; i++){
			if(arr[i]&1)
				cout << " " << i;
		}
		cout  << endl;
		
	}

	return 0;
}