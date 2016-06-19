#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 10000
#define MAX_W 10000

long long i, T, G, ans, N, MW, V[MAX_N], W[MAX_N], memo[MAX_N][MAX_W];

long long value(long long id, long long w) {
  if (id == N || w == 0) return 0;
  if (memo[id][w] != -1) return memo[id][w];
  if (W[id] > w)         return memo[id][w] = value(id + 1, w);
  return memo[id][w] = max(value(id + 1, w), V[id] + value(id + 1, w - W[id]));
}

int main() {
  scanf("%d", &T);
  while (T--) {
    memset(memo, -1, sizeof memo);

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
      scanf("%d", &V[i]);
	  W[i] = i+1;
	}
    ans = 0;
    
    MW = N;
    ans += value(0, MW);
    
    printf("%d\n", ans);
  }

  return 0;
}