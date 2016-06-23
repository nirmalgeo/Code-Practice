#include<bits/stdc++.h>
using namespace std;
int main(){

	int n, k;
	
	cin >> n >> k;
	
	int ans = k, last;
	int arr[50];
	
	for(int i=0; i<k; i++){
		cin >> arr[i];
		if(arr[i] == 0) ans--;
		last = arr[i];
	}

	for(int i=k; i<n; i++){
		cin >> arr[i];
		if( arr[i] != 0 && arr[i] == last) ans++;
	}
	
	cout << ans ;

	return 0;
}