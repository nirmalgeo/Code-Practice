//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
multiset<ll> bills;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	//freopen("in","r", stdin);
	//freopen("out","w",stdout);
	
	int n;
	while(cin >> n && n){
		bills.clear();
		ll amount = 0;
		while(n--){
			ll k,temp;
			cin >> k;
			for(ll j=1; j<=k; j++){
				cin >> temp;
				bills.insert(temp);
			}
			
			if(!bills.empty()){
				auto h = bills.end();
				h--;
				auto l = bills.begin();
				
				amount += (*h - *l);
				bills.erase(h);
				bills.erase(l);
			}
		}
		cout << amount << "\n";
	}
	
	
	return 0;
}