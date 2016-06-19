#include<bits/stdc++.h>
#define INF 1000000
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int arr[26];	
		int n;
		scanf("%d", &n);
		string s, temp;
		cin >>  s;
		memset(arr, 0, sizeof(arr));
		for(int i=0; i< s.length(); i++)   arr[ s[i] - 97]++;
		int winnerindex= -1, winnerValue = 0, winnerLen = INF;
		
		for(int i=0; i< n; i++) {
			cin>> temp;
			int count = 0;
			int hashVal = 0;
			int len = temp.length();
			for(int j=0; j<temp.length(); j++){
				if(arr[temp[j] - 97]) {
					count += arr[temp[j] - 97];
				}
			}
			//cerr << count << "\n";
			if(count > winnerValue){  winnerindex = i+1; winnerValue = count ; winnerLen=len; }
			
			else if(count == winnerValue && winnerLen > len) { winnerindex = i+1; winnerValue = count ; winnerLen=len;}
			
			else if(count == winnerValue && winnerindex > (i+1)){ winnerindex = i+1; winnerValue = count ; winnerLen=len;}
		}
		
		printf("%d\n", winnerindex);
		
	}

	return 0;
}