// uva 11286
#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int n;
	
	while(cin >> n && n){
		
		map<vector<int>, int> Map;
		map<vector<int>, int>::iterator it;
		int maxm = 1;
		while (n--){
			vector<int> V(5);
			for( int i=0; i <5; i++)
				cin >> V[i];
			sort(V.begin(), V.end());
			Map[V] += 1;
			maxm = max(maxm, Map[V]);
		}
		int tot = 0;
		for (it = Map.begin(); it != Map.end(); it++){
			if (maxm == (*it).second)
				tot += (*it).second;
		}
		
		cout << tot << endl;
	}
	
	

	return 0;
}