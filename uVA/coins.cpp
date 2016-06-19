#include<bits/stdc++.h>
using namespace std;
int main(){
	//freopen("out.txt", "w", stdout);
	int m;
	scanf("%d", &m);
	while(m--){
		bool coins[101];
		int  count[101];
		memset(coins, false, sizeof(coins));
		memset(count, 0 , sizeof(count));
		int n,k;
		scanf("%d %d", &n , &k);
		vector<int> mainset;
		for(int i=0; i< k ; i++){
			int num, temp;
			vector<int> arr;
			scanf("%d", &num);
			
			for(int j=1; j <= num*2; j++) {  scanf("%d" , &temp); arr.push_back(temp); }
			cin.ignore();
			char ch;
			cin >> ch;
			if(ch =='=') for(int i=0; i< arr.size(); i++) coins[arr[i]] = true;
			else { for(int i=0; i< arr.size(); i++) mainset.push_back(arr[i]); }
		}
		int cnt = 0, val=-1;
		for(auto &c: mainset) if(!coins[c]) count[c]++;
		
		vector<int> output;
		for(int i=1; i<= n; i++) if(!coins[i]) output.push_back(i);
			
		if(output.size() > 1){
			for(auto &c: output) if(count[c]) { val = c; cnt++;}
		}
		else { cnt = 1; val=output[0];}
		if(cnt == 1) printf("%d\n", val);
		else printf("0\n");
		
		if(m)
		printf("\n");
	}
	return 0;
}