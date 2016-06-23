#include<bits/stdc++.h>
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	long long d1,d2,d3;
	cin>>d1>>d2>>d3;
	long long arr[4];
	arr[0] = d1 * 2 + d2 * 2;
	arr[1] = d1 + d3 + d2;
	arr[2] = d1 * 2 + d3 * 2;
	arr[3] = d2 * 2 + d3 * 2;
	sort( begin(arr) , end(arr));
	cout << arr[0];
	return 0;
}