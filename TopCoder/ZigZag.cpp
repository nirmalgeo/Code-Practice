#include<bits/stdc++.h>
#define sign_val(a,b) (a>b? 1:(a==b? 0 : -1))
using namespace std;

class ZigZag{
	
	public:
	int longestZigZag(vector <int> sequence){
		vector<int> a = sequence;
		int l = sequence.size();
		int dp[l];
		memset(dp , 0 , sizeof dp);
		int last_sign = 0;
		for(int i=0; i<l; i++){
			if(i==0){
				dp[0] = 1;
				continue;
			}
			else if(a[i] != a[i-1] && (sign_val(a[i], a[i-1]) != last_sign)){
				dp[i] = dp[i-1] + 1;
				last_sign = sign_val(a[i], a[i-1]);
			}
			else{
				dp[i] = dp[i-1];
			}
		}
		
		return dp[l-1];
		 
	}
};


int main(){
	
	ZigZag a;
	vector<int> v{1,17,5,10,13,15,10, 5 , 16, 8};
	cout << a.longestZigZag(v);

	return 0;
}