//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	


// code starts here 
	string str;
	int q[1001], period[1001], cnt=0;
	
	for(int i=0; ; i++){
		cin >> str; 
		if(str == "#") break;
		cin >> q[i] >> period[i];
		cnt++;
	}
	
	priority_queue<pair<int,int>> pq;
	int k;
	cin >> k;
	for(int i=0; i < cnt; i++){
		int p = period[i];
		int qnum = q[i];
		for(int val = p; val <= 3000; val+=p){
			pq.push({-val,-qnum});
		}
	}
	
	while(k--){
		cout << -pq.top().second << "\n";
		pq.pop();
	}


// code ends here 


	return 0;
}