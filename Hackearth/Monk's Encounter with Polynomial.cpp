#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,a,b,c;
	cin>>t;
	while(t--){
		cin>>a>>b>>c;
		long long k;
		cin>>k;
		for(int i=0;;i++){
			long long val = a*i*i + b * i + c;
			if(val >=k){
				cout << i<<"\n";;
				break;
			}
		}
	}



	return 0;
}
