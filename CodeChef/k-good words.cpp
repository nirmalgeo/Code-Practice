#include<bits/stdc++.h>
#define INF (int)1e5+5
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	while(t--){
		string w;
		int k;
		cin >> w >> k;
		
		int arr[256];
		memset(arr, 0 , sizeof arr);
		int len = w.length();
		
		
		int maxCount=0;
		int maxVal = 0;
		int minVal = INF;
		int distCount = 0;
		
		for(int i=0; i<len; i++){
			if(arr[w[i]] == 0)	 distCount++;
			arr[w[i]]++;
		}
		
		for(int i=97; i<=122; i++){
			if(arr[i] > maxVal && arr[i] !=0){
				maxVal = arr[i];
			}
			if(arr[i] < minVal  && arr[i]!=0){
				minVal = arr[i];
			}
		}
		
		for(int i=97; i<=122; i++){
			if(arr[i]  == maxVal)
				maxCount++;
		}
			
		int ans= -1;
		
		if(distCount == 1)
			ans = abs(maxVal - k);
		else if( maxVal - minVal == k )
			ans = 0;
		else{
			int diff = abs(k- (maxVal-minVal));
			ans = diff * maxCount;
		}
		//cerr << maxVal << " " << minVal << " " << maxCount << "  " << distCount << " " << ans << "\n";
		if(t)
			cout << ans << "\n";
		else
			cout << ans;
	}

	return 0;
}