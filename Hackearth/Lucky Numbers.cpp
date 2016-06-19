#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;

vector<long long> v;
long long n;
long long sum =0;

long long countSetBits(long long n){
    long long count = 0;
    while (n){
      n &= (n-1) ;
      count++;
    }
    return count;
}

int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		sum = 0;
		for(long long i=1; i<=n;i++){
				if( countSetBits(i) == 2){
					sum = (sum + i)%INF;
				}
		}
		
		cout << sum <<"\n";
	}	
	return 0;
}