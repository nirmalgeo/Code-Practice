#include<bits/stdc++.h>
using namespace std;
vector<long long> v;
int main(){
	int n,q,k;
	cin>>n>>q>>k;
	v.resize(n);
	for(int i=0; i< n; i++){
		cin>>v[i];
	}
	while(q--){
		int temp;
		cin>>temp;
		if(temp == 0){
			int a, b;
			cin>>a>>b;
			v[a-1] = b;
		}
		else {
			int a,b,c,d;
			
			cin >> a>>b >> c>> d;
			
			int count = 0;
			for(int i=0 ; i <n ;i++){
				if(v[i] >= a && v[i] >= c && v[i] <=b && v[i] <=d)
					count++;
			}
			if(count >=k)
				cout << "Propose\n";
			else
				cout << "Do not propose\n";
		}
	}


	return 0;
}