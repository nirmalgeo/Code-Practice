//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


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
		vector<long long> a,b;
		long long ans = 0;
		cin >> n;
		a.resize(n);
		b.resize(n);
		
		for(int i=0; i<n; i++)	cin >> a[i];
		for(int i=0; i<n; i++)	cin >> b[i];
		
		sort(a.rbegin(), a.rend());
		sort(b.begin(), b.end());
		
		for(int i=0; i<n; i++) ans = ans+ (a[i]*b[i]);
		
			

// code ends here 

	cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}