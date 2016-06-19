#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n;
		cin>>k;
		priority_queue<long long> pq;
		long long c,sum =0;
		for(int i=0;i<n;i++){
			cin>>c;
			pq.push(c);
		}
		for(int i=0;i<k;i++){
			long long curr = pq.top();
			sum= sum + curr;
			pq.pop();
			pq.push(curr/2);
		}
		cout<<sum<<"\n";
	}
	return 0;
}