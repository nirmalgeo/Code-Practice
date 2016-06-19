#include<bits/stdc++.h>
using namespace std;
int t, n;
vector<int> v, arr;
map<vector<int>, bool> sol;
bool used[15];
void generate(int sum, int start){
	
	if(t == sum ){
		vector<int> temp;
		for(int i=0; i<n; i++){
			if(used[i]) temp.push_back(v[i]);
		}
		
		if(sol[temp]) return;
		
		else{
			int num = temp.size();
			for(int i=0; i<num-1; i++) cout << temp[i] <<"+";
			cout << temp[num-1] << "\n";
			sol[temp] = true;
			temp.clear();
			return ;
		}
	}
	
	if(sum > t || start == n) return;
	
	else{
		for(int i=start; i<n; i++){
			if(!used[i] && sum+v[i]<=t){
				used[i] = true;
				generate(sum + v[i], start+1);
				used[i] = false;
			}
		}
	}

}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	//freopen("out", "w", stdout);
	
	while(cin >> t >> n){
		if(!t && !n) break;
		v.resize(n);
		memset(used, false, n);
		for(int i=0;i < n; i++) cin >> v[i];
		cout << "Sums of "<< t << ":\n";
		generate(0,0);
	
		if(!sol.size()) cout << "NONE\n";
		v.clear();
		sol.clear();
		
	}


	return 0;
}