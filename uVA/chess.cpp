#include<bits/stdc++.h>
using namespace std;
int main(){

	int t;
	scanf("%d\n", &t);
	char c;
	int M, N;
	int answer = 0;
	for(int i = 0; i < t; ++i){
		cin>> c>> M >> N;
		answer = 0;
		if(c == 'r'){
			answer = min(M, N);
		}
		else if(c == 'Q'){
			answer = min(M, N);
		}
		else if(c == 'k'){
			answer = (((M + 1)/2) * ((N + 1)/2)) + (((M)/2) * ((N)/2));
		}
		else if(c == 'K'){
			answer = (((M + 1)/2) * ((N + 1)/2));
		}
		printf("%d\n", answer);
	}
}