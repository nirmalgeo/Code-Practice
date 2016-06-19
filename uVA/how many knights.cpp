// uva 696
#include<bits/stdc++.h>
using namespace std;
int table[550];
int main(){

	int m, n, result;
	int factor = 0;
	for(int i = 1; i <= 500; ++i){
		if(i % 4 == 1 || i % 4 == 2){
			factor += 2;
		}
		table[i] = factor;
	}
	
	while(scanf("%d %d", &m, &n) , ( m || n)){
		int minimum = min(n, m);
		int maximum = max(n, m);
		if(minimum == 1){
			result = maximum;
		}
		else if(minimum == 2){
			result = table[maximum];
		}
		else{
			result = (((m + 1)/2)*((n + 1)/2)) + ((m/2)*(n/2));
		}
		
		printf("%d knights may be placed on a %d row %d column board.\n", result, m, n);
	}
	
	return 0;

}