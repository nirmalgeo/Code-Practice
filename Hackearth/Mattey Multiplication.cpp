#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	long long m,n;
	cin>>t;
	assert(t>=1 && t<=5*10000);	
	
	for(int ii=0; ii< t; ii++){
		cin>> n >> m;
		
		long long total = n*m;
		
		long long current =0;
		vector<long long> f;
		while(1) {
			m = m / 2;
			current += (n << m);
			if(current == total) {
				f.push_back(m);
				break;
			}
			else if (current > total) {
				current -= (n<<m);
				continue;
			}
			else{
				
				f.push_back(m);
				continue;
			}
		}
		
		for(auto &c: f){
			cout << "(" << n << "<<" << m <<") + "  ;
		}
		
		cout << "\n";
	}
	
	return 0;
}