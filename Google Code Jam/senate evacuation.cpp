//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (long long)1e18
#define REP(i,a,b) for(int i=a; i<b; i++)
#define REPP(i,a,b) for(int i=a; i<=b; i++)
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
typedef long long ll;


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){
	
// code starts here 
		
		vector<int> arr;
		vector<float> tot;
		int n;
		
		cin >> n;
		arr.resize(n);
		
		REP(i, 0, n) cin >> arr[i];
		
		priority_queue<pair<int, char>> pq;
		
		REP(i, 0 , n){
			pq.push({arr[i], 'A'+i});
		}
		string ans = "";
		
		int cnt = 1;
		while(!pq.empty()){
			auto top = pq.top();
			
			if(pq.size()%2 && top.first == 1 && pq.size() > 1){
				if(ans != "" && ans[ans.length()-1] != ' ' ) ans += " ";
				pq.pop();
				ans += top.second;
				ans += " ";
				cnt = 0;
				continue;
			}
			else {
				pq.pop();
				int x = top.first;
				char ch = top.second;
				x--;
				if(x > 0) pq.push({x, ch});
				
				
				ans+= ch;
				cnt++;
				
				if(cnt == 3 && !pq.empty()) {
					ans+= " ";
					cnt = 1;
				}
			}
		}
		
		
// code ends here 

	
	 cerr << "test " << cas << " done" << endl;

	cout << "Case #"<< cas << ": " << ans;
	cout << "\n";


	}

	return 0;
}