//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (long long)1e18
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};

typedef long long ll;

inline int pow(int x, int n) {
	if (n == 0) return 1;
	if (n % 2 != 0) return x * pow(x, n - 1);
	int st = pow(x, n/2);
	return st * st;
}

inline long long tobase(string s, int base, int ascii[]){
	long long ans = 0;
	int temp;
	for(int i=0; i<s.length() ; i++){
		temp = ascii[s[i]];
		ans = ans* base;
		ans += temp;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("B-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
			
		ll b,n;
		cin >> b >> n;
		vector<int> B;
		B.resize(b);
		
		for(int i=0;i <b; i++) cin >> B[i];
		
		ll low = 0, high = inf, mid, count = 0, ans;
		while(low < high){
			mid = (low+high)/2;
			ll sum = 0;
			for(int i=0; i <b ;i++)
				sum += ( mid / B[i] + 1);
			if(sum >= n)
				high = mid;
			else{
				low = mid +1;
				count = sum;
			}
		}
		
		for(int i=0; i<b; i++)
			if(low%B[i]==0){
				count++;
				if(count == n){
					ans = i+1;
					break;
				}
			}
		
// code ends here 

	cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}