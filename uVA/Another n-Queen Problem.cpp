#include<bits/stdc++.h>
using namespace std;
char board[16][16];
int num=0;
int n;
bitset<30> row, rd , ld;
void backtrack(int c){
	if(c == n){
		num++;
		return;
	}
	for(int r=0; r<n; r++){
		if(board[r][c] != '*' && !row[r] && !ld[r-c+n-1] && !rd[r+c]){
			row[r] = rd[r+c] = ld[r-c+n-1] = true;
			backtrack(c+1);
			row[r] = rd[r+c] = ld[r-c+n-1] = false;
		}
	}
}


int main(){

	int t = 1;
	while(scanf ( "%d", &n) && n ){
		for(int i=0; i< n; i++)
			scanf("%s",&board[i]);
		num =0;
		backtrack(0);
		
		printf("Case %d: %d\n",t++,num);
	
	}
	return 0;
}