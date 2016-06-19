#include<bits/stdc++.h>
using namespace std;
int main(){
	//ios_base::sync_with_stdio(0);
	long long q, c;
	stack<long long> food;
	scanf("%lld",&q);
	while(q--){
		long long a;
		scanf(" %lld",&a);
		if(a==1){
			if(food.empty())
				printf("No Food\n");
			else{
				a = food.top();
				food.pop();
				printf("%lld\n",a);
			}
		}
		else if(a==2){
			scanf("%lld",&a);
			food.push(a);
		}
	}
	return 0;
}