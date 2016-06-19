// uva 11572

#include<bits/stdc++.h>
using namespace std;

#define maxn (int)(1e9)+1

int t, n, x, ans, cnt, block;
map<int, int> lastseen;
/*cnt stores the number of unique snowflakes seen so far, and block stores the index of the last snowflake that wasn’t unique. */


int main() {
    cin >> t;
	while(t--) {
		cin >> n;
		lastseen.clear();
		ans = 0, cnt = 0, block = 0;
		for(int i=1; i<=n; i++) {
			cin >> x;
			int lx = lastseen[x];
			if(lx != 0) {
			block = max(block, lx);
			cnt = i-block-1;
			}	
			cnt++;
			lastseen[x] = i;
			ans = max(ans, cnt);
		}
		cout << ans << '\n';
    }
}