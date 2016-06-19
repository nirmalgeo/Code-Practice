#include<bits/stdc++.h>
using namespace std;
vector<int> win(101), loss(101);
int main(){
	int n,k;
	while(1){
		
		cin>>n;
		if(n==0)
			break;
		
		cin>>k;

		assert(n>=1 && n<=100);
		assert(k>=1 && k<=100);
		cin.ignore();
		int tot = n*(n-1)*k/2;
		int p1,p2;
		char m1[15],m2[15];
		while(tot--){
			scanf("%d %s %d %s", &p1 , m1 , &p2 , m2);
			assert(p1 != p2);
			string s1(m1), s2(m2);
			
			assert(s1 == "rock" || s1 == "scissors" || s1 == "paper");
			assert(s2 == "rock" || s2 == "scissors" || s2 == "paper");
			
			if(s1!=s2){
					if(s1 == "rock"){
						if(s2=="paper"){
							win[p2]++;
							loss[p1]++;
						}
						else{
							win[p1]++;
							loss[p2]++;
						}
					}
				
					else if(s1 == "paper"){
						if(s2 == "rock"){
							win[p1]++;
							loss[p2]++;
						}
						else{
							win[p2]++;
							loss[p2]++;
						}
					}
						
					else if(s1 == "scissors"){
						if(s2== "paper"){
							win[p1]++;
							loss[p2]++;
						}
						else{
							win[p2]++;
							loss[p1]++;
						}
					}
			}
			
		}
		for(int i=1;i<=n;i++){
			float f;
			if(win[i] == 0 && loss[i] == 0)
				f= 0;
			else
				f =  (float)win[i] / (float)(win[i] + loss[i]);
			printf("%0.3f\n",f);
		}
		
		for(int i=1;i<=n;i++){
				win[i] = 0;
				loss[i]=0;
		}
		
		//fill(win.begin(), win.end(), 0);
		//fill(loss.begin(), loss.end(), 0);
		printf("\n");
	}


	return 0;
}