#include<bits/stdc++.h>
using namespace std;
//int v[1<<20];
vector<int> v;
int check(int mid,int k, int n){
	int prev = v[0] + mid;
	k--;
	for(int i=1;i<n;i++){
		if(prev + mid >= v[i])
			continue;
		if(k == 0)
			return 0;
		prev = v[i] + mid;
		k--;		
	}
	return 1;
}

int main(){
	int n,k;
	cin>>n>>k;
	v.resize(n);
	for(int i=0;i<n;i++){
		cin>>v[i];
	}
	sort(v.begin(), v.end());
	int l=1,h=1e7,mid;
	
	while(l <= h){
		mid = (l+h)/2;
		//cout << mid << "\n";
		int ret = check(mid,k,n);
		int ret2 = check(mid-1,k,n);
		if( ret && ret2==0)
			break;
		if(ret == 0){
			l = mid +1;
		}
		else {
			h = mid - 1;
		}
	}
	cout << mid;


	return 0;
}	