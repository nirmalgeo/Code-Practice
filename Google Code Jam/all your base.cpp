//nirmalgeo25 template
#include<bits/stdc++.h>
#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice (1).in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){
	
// code starts here 
		string s;
		cin >> s;
		long long base = 0, ans =0;
		
		int ascii[256];
		
		memset(ascii, 0 , sizeof ascii);
		
		REP(i, s.length())
			if(ascii[s[i]] == 0)
				ascii[s[i]] = ++base;
		
		if(base<2) base = 2;
		
		REP(i, s.length()){
			long long temp = ascii[s[i]];
			if(temp == 1) ;
			else if(temp == 2) temp = 0;
			else temp--;
			ans = ans * base;
			ans += temp;
		}
		
		
		
// code ends here 

	cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}