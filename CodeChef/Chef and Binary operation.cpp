#include<bits/stdc++.h>
using namespace std;
int main(){

	int t;
	cin >> t;
	
	while(t--){
		string a, b;
		cin >> a ;
		cin >> b ;
		
		int n = a.length();
		bool ans = true;
		int ansVal = 0;
		
		int oneCount = 0 , zeroCount = 0, totOne, totZero;
		for(int i=0; i<n; i++){
			if(a[i] != b[i]){
				if(a[i] == '1')
					oneCount++;
				else
					zeroCount++;
			}
		}
		
		int compCount = min(oneCount, zeroCount);
		ansVal += compCount;
		
		compCount*=2;
		
		for(int i=0; i<n; i++){
			if(compCount == 0) break;
			
			if(a[i] != b[i]){
				a[i] = b[i];
				compCount--;
			}
		}
		
		oneCount = zeroCount = 0;
		totOne = totZero = 0;
		for(int i=0; i<n; i++){
			if(a[i] != b[i]){
				if(a[i] == '1') oneCount++;
				else zeroCount++;
			}
			else{
				if(a[i] == '1') totOne++;
				else totZero++;
			}
		}
		
		if((oneCount > 0 && totZero == 0) || (zeroCount > 0  && totOne == 0))
			ans = false ;
		
		if(ans){
			cout << "Lucky Chef\n";
			ansVal += (zeroCount + oneCount);
			cout << ansVal << "\n";
		}
		else
			cout << "Unlucky Chef\n";
	
	}
	return 0;
}