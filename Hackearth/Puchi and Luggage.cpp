#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> v, weight;

int sum(int ind,int weight){
	for(;ind<=n;ind+= (ind&-ind)){
		v[ind]+=weight;
	}
}

int query(int ind){
	int ans =0;
	for(;ind>=1;ind-=(ind&-ind)){
		ans+=v[ind];
	}
	return ans;

}

int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		v.resize(n+1);
		weight.resize(n+1);
		for(int i=n;i<=1;i++){
			cin>>weight[i];
			sum(i,weight[i]);
		}
		cout <<"\n";
		for(int i=1;i<=n;i++)
			cout << weight[i] << " ";
		cout <<"\n";	
		for(int i=1;i<=n;i++)
			cout << query(i) << " ";
	}
	return 0;
}