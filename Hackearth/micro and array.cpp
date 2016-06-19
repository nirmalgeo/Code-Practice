#include<bits/stdc++.h>
#define MAXN 100005
#define INF 200000
using namespace std;

int arr[MAXN];
vector<int> t[4*MAXN];

bool cmp(int a, int b) {return a>=b;}	
 
void build (int a[], int v, int tl, int tr) {
	if (tl == tr)
		t[v] = vector<int> (1, a[tl]);
	else {
		int tm = (tl + tr) / 2;
		build (a, v*2, tl, tm);
		build (a, v*2+1, tm+1, tr);
		merge (t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
			back_inserter (t[v]));
	}
}


int query (int v, int tl, int tr, int l, int r, int x) {
	if (l > r)
		return INF;
	if (l == tl && tr == r) {
		for(auto &c: t[v])
			cout << c << " ";
		cout << "\n";
		vector<int>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
		if (pos != t[v].end())
			return (pos - t[v].begin());
		return -1;
	}
	int tm = (tl + tr) / 2;
	return max(
		query (v*2, tl, tm, l, min(r,tm), x),
		query (v*2+1, tm+1, tr, max(l,tm+1), r, x)
	);
}


void update (int v, int tl, int tr, int pos, int new_val) {
	t[v].erase (find (t[v].begin(), t[v].end(), arr[pos]));
	t[v].push_back (new_val);
	if (tl != tr) {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update (v*2, tl, tm, pos, new_val);
		else
			update (v*2+1, tm+1, tr, pos, new_val);
	}
	else
		arr[pos] = new_val;
}



int main(){
	int n , q;
	
	cin >> n >> q;

	for(int i=0; i<n; i++) cin >> arr[i];
	sort(begin(arr), end(arr));	

	build(arr,1, 0 , n-1);
	
	while(q--){
		int temp;
		
		cin >> temp;
		
		if(temp == 0){
			int x, val;
			cin >> x >> val;
			update(1, 0, n-1, x-1, val); 
		}
		else {
			int  val;
			cin >> val;
			cout << query(1, 0 , n-1, 0 , n-1, val) << "\n";
		}
	}



	return 0;
}