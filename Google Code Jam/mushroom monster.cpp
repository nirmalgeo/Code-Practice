//nirmalgeo25 template
#include<bits/stdc++.h>
#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define REPP(i,a,n) for(int (i)=a;(i)<(int)(n);(i)++)
#define INF (int)1e9
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};

inline int pow(int x, int n) {
	if (n == 0) return 1;
	if (n % 2 != 0) return x * pow(x, n - 1);
	int st = pow(x, n/2);
	return st * st;
}

inline long long tobase(string s, int base, int ascii[]){
	long long ans = 0;
	int temp;
	REP(i, s.length()){
		temp = ascii[s[i]];
		ans = ans* base;
		ans += temp;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		
		int n;
		cin >> n;
		vector<int> v;
		v.resize(n);
		REP(i, n)
			cin >> v[i];
		
		int y=0, z=0;
		
		REPP(i,1,n)
			if(v[i] < v[i-1])
				y+= abs(v[i]-v[i-1]);
				
		int rate = -1;
		REPP(i,1,n)
			rate = max(rate, v[i-1] - v[i]);
		
		//cout << rate << "\n";
		for(int i=0; i< (n-1) ; i++)
			z += min(rate, v[i]);
		
		

// code ends here 

	cout << "Case #"<< cas << ": "<< y << " " << z <<"\n";


	}

	return 0;
}