#include<bits/stdc++.h>
using namespace std;

int main(){
	long long a, b , p;
	
	cin >> a >> b >> p;
	
	double baseArea = 0.5 * a * b;
	baseArea = baseArea * p/100;
	double calc;
	for(int i=1; i<=a; i++){
		for(int j=1; j<=b; j++){
		calc = 0.5 * i * j;
		if(calc < baseArea) break;
		}
	}

	printf("%0.2lf", calc);


	return 0;
}