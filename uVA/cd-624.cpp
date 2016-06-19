#include<bits/stdc++.h>
using namespace std;

int main(){
	cin.tie(0);

	int T,n;
	
	while(scanf("%d",  &T) != EOF){
		scanf("%d", &n);
		vector<int> v;
		v.resize(n);
		
		for(int i=0; i<n; i++)
			scanf("%d", &v[i]);
			
		vector<int> out;
		int maxVal = 0;
		int count = 0;
		
		for(int i=0; i< (1<<n); i++){
			int sum = 0;
			vector<int> temp;
			bool found = true;
			for(int j=0; j< n; j++){
				if(i & (1<<j)){
					sum+= v[j];
					temp.push_back(v[j]);	
				}
				if(sum > T) { found = false; break;}
			}
			if(!found) {temp.clear(); continue;}
			
			if(sum >= maxVal){
				if(sum == maxVal && temp.size() < out.size()) continue;
				maxVal = sum;
				out.clear();
				out = temp;
			}
			
		}
		
		for(auto &c: out)
			cout << c << " ";
		cout << "sum:"<<maxVal<<"\n";
	
	
	}

	return 0;
}