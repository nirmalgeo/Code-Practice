#include<bits/stdc++.h>
using namespace std;
int main(){
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);

	int n;
	set<int> s;
	
	for(int i=0; i<=20; i++){
		s.insert(i);
		s.insert(i*2);
		s.insert(i*3);
	}
	s.insert(50);
	vector<int> values;
	for(auto c: s)
		values.push_back(c);
	
	int t = values.size();
	int perm = 0;
	int comb = 0;
	bool visited[70][70][70];
	
	
	
	while(cin >> n  && n >0 ){
		perm = 0;
		comb = 0;
		memset(visited, false, sizeof visited);
		
		
		
		for(int i=0; i< t; i++)
			for(int j=0; j< t; j++)
				for(int k=0; k<t; k++){
					if( values[i] + values[j] + values[k] == n){
						perm++;
						if(!visited[values[i]][values[j]][values[k]] ){
							visited[values[i]][values[j]][values[k]] = visited[values[i]][values[k]][values[j]] =  true;
							visited[values[j]][values[i]][values[k]] = visited[values[j]][values[k]][values[i]] =  true;
							visited[values[k]][values[j]][values[i]] = visited[values[k]][values[i]][values[j]] =  true;
							comb++;
						}				
					}
				}
				
		if(!perm && !comb){
			cout << "THE SCORE OF "<<n << " CANNOT BE MADE WITH THREE DARTS.\n";
			cout << "**********************************************************************\n";
		}
		else{
			cout << "NUMBER OF COMBINATIONS THAT SCORES "<<n<<" IS "<<comb<<".\n";
			cout << "NUMBER OF PERMUTATIONS THAT SCORES "<<n<<" IS "<<perm<<".\n";
			cout << "**********************************************************************\n";
		}
	
	
	}
	cout << "END OF OUTPUT";


	return 0;
}
