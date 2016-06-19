// UVA 10855
#include<bits/stdc++.h>
 
using namespace std;
 
int N, n;
int ans[4];
char big[10000][10000], small[4][10000][10000];
 
bool exists(int r, int c, int b) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(big[r + i][c + j] != small[b][i][j]) return false;
    return true;
}
 
void check() {
    ans[0] = ans[1] = ans[2] = ans[3] = 0;
    for(int i = 0; i < N - n + 1; i++) {
        for(int j = 0; j < N - n + 1; j++) {
            for(int k = 0; k < 4; k++) {
                if(exists(i, j, k)) ans[k]++;
            }
        }
    }
}
 
int main() {
    for(;;) {
        scanf("%d %d\n", &N, &n);
        if(N == 0 && n == 0) break;
 
        for(int i = 0; i < N; i++)
            gets(big[i]);
        for(int i = 0; i < n; i++)
            gets(small[0][i]);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                small[1][i][j] = small[0][n - 1 - j][i];
                small[2][i][j] = small[0][n - 1 - i][n - 1 - j];
                small[3][i][j] = small[0][j][n - 1 - i];
            }
        check();
        printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
    }
}