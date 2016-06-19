#include<bits/stdc++.h>
using namespace std;

bool sel[5];
vector<int> v{1,2,3,4,5};
int n = 5;

vector<int> perm;
static int cnt = 0;
void generate(int at){
	if(at == n){
		for(int i=0; i < n ;i++)	
			cout << perm[i] << " " ;
		cout << "\n";
		cnt++;
	}
	else{
		
		for(int i=0; i<n; i++)
		{
			if(!sel[i]){
				
				sel[i] = true;
				perm[at] = v[i];
				generate(at+1);
				sel[i] = false;
				
			}
		}
	}
}

void solve(int at){

	if(at == n){
			for(int i=0; i < n ;i++)	
				if(sel[i])
					cout << v[i] << " ";
			cout << "\n";
			cnt++;
	}
	else{
		sel[at]= true;
		solve(at+1);
		sel[at] = false;
		solve(at+1);
	}

}


int main(){
	memset(sel, false, sizeof sel);
	
	perm.resize(n);
	cout << "Combination:\n";
	cnt=0;
	solve(0);
	cout << "Count : " << cnt  << "\n"; 
	
	
	cout << "Permutation:\n";
	generate(0);
	cout << "Count : " << cnt  << "\n"; 
	return 0;
}