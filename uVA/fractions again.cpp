#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> pairs;
int main(){
	int k;
	while(scanf("%d", &k) != EOF){
		
		int total=0;
		pairs.clear();
		for(int i=k+1; i<=2*k; i++){
			if((i*k)%(i-k) == 0){
				int temp = (i*k)/(i-k);
				pairs.push_back(make_pair(temp,i));
				total++;
			}
		}
			
		printf("%d\n",total);
		for(int i=0;i<pairs.size(); i++)
			printf("1/%d = 1/%d + 1/%d\n",k,pairs[i].first, pairs[i].second);
	
	}
	
	return 0;
}