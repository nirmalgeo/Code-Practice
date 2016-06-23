#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int n;
	cin >> n;
	
	int arr[n];
	
	for(int i=0; i<n; i++)
		cin >> arr[i];
	
	auto it = find(arr, arr+n, 1);
	int fpos = it - arr + 1;
	it = find(arr, arr+n , n);
	int lpos = it - arr + 1;
	
	//cerr << fpos << " " << lpos << "\n";
	
	int a1 = abs(n - fpos);
	int a2 = abs(1 - fpos);
	int a3 = abs(n - lpos);
	int a4 = abs(1 - lpos);
	
	int ans = 0;
	
	ans = max(a1, a2);
	ans = max(ans, a3);
	ans = max(ans , a4);
	
	cout << ans ;
	


	return 0;
}