#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		ll a,b;
		cin>>a>>b;
		if(a==b)
			cout<<"="<<"\n";
		else if(a<b)
			cout<<"<"<<"\n";
		else
			cout<<">"<<"\n";
	}

	return 0;
}