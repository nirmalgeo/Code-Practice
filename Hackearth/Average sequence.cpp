#include<bits/stdc++.h>
#define INF 1000000000
using namespace std;
int main(){
	int n;
	vector<long long> listA, listB;
	cin>>n;
	listB.resize(n);
	listA.resize(n);
	assert(n>=1 && n<=100);
	for(int ii=0;ii<n;ii++){
		cin>>listB[ii];
		assert(listB[ii] >=1 && listB[ii] <= INF);
	}
	
	listA[0] = listB[0];
	long long currentsum = listA[0];
	for(int ii=1; ii<n; ii++){
		long long temp = (ii+1)*listB[ii] - currentsum;
		listA[ii] = temp;
		currentsum += temp;
	}
	
	for(auto &c: listA)
		cout << c << " ";


	return 0;
}