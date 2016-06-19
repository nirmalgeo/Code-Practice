// uva 12356

#include<bits/stdc++.h>
using namespace std;
int LS[100005];
int RS[100005];
int main(){
	int s,b;
	while(scanf("%d %d", &s , &b) && s && b){
		int L, R;
		for(int i=1; i<= s; i++){
			LS[i] = i-1;
			RS[i] = i+1;
		}		
		
		for(int i = 0; i < b; i++) {
            scanf("%d %d", &L, &R);
            if(LS[L] < 1) printf("* ");
            else printf("%d ", LS[L]);
            if(RS[R] > s) printf("*\n");
            else printf("%d\n", RS[R]);
 
            LS[RS[R]] = LS[L];
            RS[LS[L]] = RS[R];
			
			//cerr << LS[L] << " " << RS[R] << "\n";
        }
        printf("-\n");
	
	}
	return 0;
	
}