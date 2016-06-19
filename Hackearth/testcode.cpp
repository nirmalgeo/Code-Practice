#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
long long sum=0;
long long n;
bool countSetBits(long long n)
{
    long long count = 0;
    while (n){
      n &= (n-1) ;
      count++;
	  if(count > 2)
		return false;
    }
	if(count == 2)
		return true;
	else
		return false;
}
 
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
			
		for(long long i=1; i<=n;i++){
				if( countSetBits(i)){
					sum += (i%INF);
				}
		}
		
		cout << sum%INF <<"\n";
	}	
	return 0;
}