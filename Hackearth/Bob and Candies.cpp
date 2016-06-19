#include<bits/stdc++.h>
using namespace std;

int arr[1000005];
int main(){
	int n, x;
	scanf("%d %d",&n, &x);
	
	for( int i=0; i<n; i++ ){
		scanf("%d", &arr[i]);
	}
	
	int sum, val;
	bool found = false;
	for (int i = 0; i < (1 << n); i++) { 
		sum = 0;
		for (int j = 0; j < n; j++) 
			if (i & (1 << j)) 
				sum += arr[j]; 
		if (sum == x){
			val = i;
			found =true;
			break; 
		}
	}
	

	
	if(!found)
		printf("-1");
	else{
		int cnt =0;
		for(int i=0; i<n; i++){
			if( val & (1 << i)){
				if(!cnt)
					printf("%d", i+1);
				else
					printf(" %d", i+1);
				cnt = 1;
			}
		}
		
	}
	return 0;
}