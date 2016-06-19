#include<bits/stdc++.h>
using namespace std;
vector<int> v;
bool sel[25];
vector<int> out;
int maxVal=0;
int T,n;
void solve(int at){
	if(at == n){
		int sum =0;
		vector<int> temp;
		for(int i=0; i<n; i++)
			if(sel[i]){
				sum+= v[i];
				temp.push_back(v[i]);
			}
		
		if(sum >= maxVal && sum <= T){
			if(sum == maxVal && temp.size() < out.size()) return;
			maxVal = sum;
			out.clear();
			out = temp;
			temp.clear();
		}
	
	}
	
	else{
		sel[at] = true;
		solve(at+1);
		sel[at] = false;
		solve(at+1);
	}
	
}


int main(){
	
	
	while(scanf("%d",  &T) != EOF){
		scanf("%d", &n);

		v.resize(n);
		memset(sel, false, sizeof sel);
		
		
		for(int i=0; i<n; i++)
			scanf("%d", &v[i]);
	
		solve(0);
		
		for(auto &c: out)
			cout << c << " ";
		cout << "sum:"<<maxVal<<"\n";
		
		out.clear();
		maxVal = 0;
	}

}