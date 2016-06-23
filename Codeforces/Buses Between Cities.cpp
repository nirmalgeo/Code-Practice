#include<bits/stdc++.h>
using namespace std;
int main(){

	// code starts here

	int  B[2000];
	memset(B, -1, sizeof B);
	
	
	int a, ta;
	cin >> a >> ta;
	int b, tb;
	cin >> b >> tb;
	
	int f,s;
	scanf("%d:%d", &f, &s);
	
	int start=300;
	int end = 24*60-1;
	
	int cnt = 1;
	for(int i=start; i<=end; ){
		B[i] = cnt;
		B[i+tb] = cnt;
		i+=b;
		cnt++;
	}
	
	start = f*60+s;
	end = start+ ta;
	
	set<int> se;
	for(int i=start; i< end; i++){
		if(B[i] != -1)
			se.insert(B[i]);
	}
	
	
	cout << se.size();


	// code ends here 
	return 0;
}