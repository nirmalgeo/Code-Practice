#include<bits/stdc++.h>
using namespace std;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	int arr[100000];
	int count = 0;
	int val = 3;
	for(int i=3; i<=100000; i++){
		if(count && count%2==0) { val++; count = 0;}
		arr[i] = val;
		count++;
	}
	
	while(t--){
		long long n, p;
		cin >> n >> p;
		int val = arr[n];
		p--;
		while(p--){
			//cout << val << "\n";
			val = arr[val];
		}
		cout << val << endl;
	}

	return 0;
}