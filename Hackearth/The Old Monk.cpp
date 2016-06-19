#include<bits/stdc++.h>
using namespace std;
bool func(int i, int j){
	return (i>j);
}
int main(){
	int t;
	vector<long long> a,b;
	long long monk;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		long long var;
		for(int i=0;i<n;i++){
			cin>>var;
			a.push_back(var);
		}
		
		for(int i=0;i<n;i++){
			cin>>var;
			b.push_back(var);
		}
		monk=0;
		for(int i=0;i<n;i++){
			int low=0,mid,high=n-1;
			long long curr;
			while(low<=high){
				mid = (low+high)/2;
				if(b[mid] >= a[i]){
					low=mid +1;
					curr = mid - i;
				}
				else
					high = mid -1;
			}
			monk = max(monk, curr);
		}
		cout << monk << "\n";
		a.clear();
		b.clear();
	}
	return 0;
}