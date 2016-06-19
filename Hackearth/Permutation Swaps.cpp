#include<bits/stdc++.h>
using namespace std;
vector<int> arr, perm, basecopy;
set<pair<int,int>> s;
int main(){

int t;
cin>>t;
while(t--){
	int n,m;
	cin>> n >> m;
	arr.resize(n);
	perm.resize(n);
	basecopy.resize(n);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	for(int i=0; i<n;i++){
		cin>>perm[i];
	}
	basecopy = arr;
	int a,b;
	for(int i=0;i<m; i++){
		cin>>a>>b;
		if(a>b	)
			swap(a,b);
		s.insert({a-1,b-1});
	}
	
	for(auto &c: s)
		cout << c.first << " " << c.second << "\n";
		
	bool found =true;
	int permcount = 0;
	do{
		for(int i=0;i<n;i++){
			cout << arr[i] << " ";
		}
		cout << "\n";
		if(arr != basecopy){
			int x , y, val;
			for(int i=0; i< n; i++){
				if(arr[i] != basecopy[i]){
					x=i;
					val = basecopy[i];
					break;
				}
			}
			
			for(int i=0; i<n; i++)
			{
				if(basecopy[i] == val){
					y = i;
					break;
				}
			}
			
			if(y>x)
				swap(x,y);
				
			if(s.find({x-1,y-1}) == s.end()){
				found = false;
				break;
			}
		}
	}while(next_permutation(arr.begin(), arr.end()));
	
	if(!found)
		printf("NO\n");
	else
		printf("YES\n");

}

	return 0;
}