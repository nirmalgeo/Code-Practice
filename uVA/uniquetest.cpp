#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("out", "w", stdout);

	int t;
	cin >> t;
	while(t--){
		map<int,int> m;
		priority_queue<int> pq;
		int cnt = 0;
		int temp, lastindex, n, lastconflict=-1;
		cin >> n;
		
		
		for(int i=0; i<n; i++){
			cin >> temp;
			
			if(m[temp] != 0){
				if(lastconflict==-1) lastconflict = m[temp];
				pq.push(cnt);
				cnt = i - lastconflict;
				m[temp] = i;
				lastconflict = i;
			}
			else {
				cnt++;
				m[temp] = i;
			}
		}
		
		pq.push(cnt);
	
		
		cout << pq.top() << "\n";
		
	}
	
	




	return 0;
}