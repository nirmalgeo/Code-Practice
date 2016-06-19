#include<bits/stdc++.h>
using namespace std;
vector<int> v;
vector<int> temp;
int main(){
	int n, q, x, val;
	
	cin >> n >> q;

	v.resize(n+1);
	while(q--){
		cin >> x >> val;
		v[x] += val;
		temp = v;
		long long sum = 0;
		sort(temp.rbegin(), temp.rend());
		
		sum = temp[0];
		int last = 1;
		for(int i=1; i<n; i++){
			if(temp[i] != temp[i-1])
				last = i+1;
				
			sum += last*temp[i];
		}
			
		
		cout << sum <<"\n";
	}




	return 0;
}