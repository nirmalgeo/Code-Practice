// simple but interesting uva 146
#include<bits/stdc++.h>
using namespace std;
int main(){
	
	while(1){
		char p[51], q[51];
		int n;
		gets(p);
		
		if(p[0] == '#')
			break;
		
		n = strlen(p);
		
		if(next_permutation(p, p+n)){
			puts(p);
		}
		else{
			printf("No Successor\n");
		}
	}

	return 0;
}