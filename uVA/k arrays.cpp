#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
vector<long long> v[11] ;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n,k;
		scanf("%d %d", &n, &k);
		for(int i=0; i<k; i++){
			v[i].resize(n);
			for(int j=0 ; j < n; j++){
				scanf("%lld", &v[i][j]);
			}
		}
		
		long long val, numer, min = INF, max = -1;
		int denom, count;
		long long maxVal = -1, minVal = INF, maxCount , minCount;
	
		
		
		for(int i=1; i < (1<<n); i++){
			count = 0;
			val =0;
			numer = 1;
			
			for(int j=0 ; j < n; j++){
				if(i & (1<<j)){
					count++;
					val = 0;
					
					for(int ii=0 ; ii < k ; ii++){
						val += v[ii][j] ;
						//cerr << v[ii][j] << " ";
						//cerr << val << " ";
					}
					numer = numer * val % INF;
					denom = count;
				}
			}
			val = numer / denom;
			val %= INF;
	
			//cerr << val << " " << denom << "\n";
			if(val >  maxVal){
				maxVal = val;
				maxCount = denom;
			}
			
			else if(val == maxVal && denom < maxCount){
				maxCount = denom;
			}
			
			if(val < minVal){
				minVal = val;
				minCount = denom;
			}
			else if(val == minVal && denom > minCount ){
				minCount = denom;
			}
			
		}
		
		cout  << (maxVal^minVal) << " " << (maxCount^minCount)<< "\n";
	}



	return 0;
}