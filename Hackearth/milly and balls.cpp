#include<iostream>

using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	
	while(t--){
		long long n, k, total=0;
		
		cin >> n >> k;
		
		long long  val = n * (n+1) / 2;
		
		while(k > total) total = total + val; 
		//cerr << total << "\n";
		
		//total = total - val;
			
		cout << abs(total - k) << "\n";
	}
	
	
	return 0;
}