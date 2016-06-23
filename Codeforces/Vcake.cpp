#include<bits/stdc++.h>
using namespace std;
unsigned long long r, c, m, j ,k;
bool check() {
		
	unsigned long long temp, oth, maxx = m, a , b, val, i;

	if(m%r == 0){
		temp = r;
		oth = c;
	}
	else{
		temp = c;
		
		oth = r;
	}
		
	if( m%temp == 0 && j%temp == 0 && k%temp == 0)
		if( ((m/temp) + (j/temp) + (k/temp)) == oth )
			return true;

	//cout << "test";
	maxx = max(max(m, j), k);
	
	if(maxx == m) {  a= j; b = k; }
	else if( maxx == j) { a= m; b = k; }
	else { a= m; b = j; }
	
	temp = max(r, c);
	oth = min(r, c);
	
	oth = maxx / temp;
	
	for(i = 1; i<temp; i++){
		val= abs(temp - i);
		if((a%i == 0 && b%val == 0  ) || ( b%i == 0  && a%val == 0) )
			return true;
	}
	return false;
}

int main(){
	int t;
	cin >> t;
	while(t--){

		
		cin >> r >> c >> m >> j >> k;
	
		bool found = false;
		
		if(r*c == m+j+k){
			
			found = check();
		
		}
	
		if(found) cout << "Yes\n";
		else cout << "No\n";
	
	}



	return 0;
}