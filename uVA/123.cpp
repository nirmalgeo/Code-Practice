#include<bits/stdc++.h>
using namespace std;
int main(){
	long long l=0;
	for(int i=0; i< 70 ; i++){
		l |= ( 1 << i);
		printf("%lld \t  %d \n", l , i);
	}

	return 0;
}