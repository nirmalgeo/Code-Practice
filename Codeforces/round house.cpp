#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b;
	cin >> n >> a >> b;

	bool up = true;
	if(b < 0) up = false, b= b*-1;
	
	for(int i=1; i<=b; i++){
		if(up) a++;
		else a--;
		
		if(up && a==(n+1))  a=1;
		if(!up && a==0)  a=n;
	}
	
	cout << a ;
	
	return 0;
}