#include<iostream>
#include<map>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while(t--){
		long long n, x , y ;
		cin >> n >> x >> y;
		map<long long, int> m;
		
		long long ranks = n - x;
		long long count = 0;
		
		for(long long i=0;i <= y && count <= ranks; i++) count++;
		
		cout << count << "\n";
		
	
	}
	
	
	return 0;
}