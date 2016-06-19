#include<bits/stdc++.h>
#define INF (int)(1e9+7)
using namespace std;

typedef vector<int> vi;
#define LSOne(S) (S & (-S))

vector<int> arr;

int computegcd(int x, int pos){
	int sum=0;
	int cnt= 1;
	for(auto &c: arr) {
		if ( pos++ == cnt) 
		sum+= __gcd(c,x);
	return sum;
}



class FenwickTree {
private:
  vi ft;

public:
  FenwickTree() {}
  // initialization: n + 1 zeroes, ignore index 0
  FenwickTree(int n) { ft.assign(n + 1, 0); }

  int rsq(int b, int x) {                                     // returns RSQ(1, b)
    int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
    return sum; }

  int rsq(int a, int b, int x) {                              // returns RSQ(a, b)
    return rsq(b,x) - (a == 1 ? 0 : rsq(a - 1,x)); }

  // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
  void adjust(int k, int v) {                    // note: n = ft.size() - 1
    for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int main() { 

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,temp;
	cin >> n;
	FenwickTree ft(10); 
  
	for(int i=1; i<=n; i++){
		cin >> temp;
		ft.adjust(i,temp);
	}
	
	int q;
	cin >> q;
	while(q--){
		char ch;
		int x, y;
		cin >> ch;
		if(ch == 'U')
		{
			cin >>  x >> y;
			ft.adjust(x, y);
		}
	
		else{
			cin >> x >> y;
			cout << ft.rsq(x,y,x) <<"\n";
		}
	}
	
  return 0;
} 
