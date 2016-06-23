#include<bits/stdc++.h>
using namespace std;
long long arr[100005];
int main(){
	int n;
	scanf("%d", &n);
	
	for(int i=0; i< n; i++)
		scanf("%lld", &arr[i]);
	
	long long sumeven = 0;
	long long smallodd = LLONG_MAX;
	for(int i=0; i<n; i++){
		if(arr[i]&1 && arr[i] < smallodd)
			smallodd = arr[i];
		
		sumeven+= arr[i];
	}
	
	if(sumeven&1)
		sumeven -= smallodd;
	
	printf("%lld", sumeven);

	return 0;
}