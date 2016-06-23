#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n, k, temp;
	cin >> n >> k;
	
	temp = n/k;
	temp++;
	cout << temp*k;


	return 0;
}