#include<bits/stdc++.h>
using namespace std;
bool isPrime[100];
vector<int> v;
int n;
bool used[20];

void generatePrime(){
	memset(isPrime, false, sizeof isPrime);
	isPrime[2] = isPrime[3] = true;
	
	for(int i=4; i<100; i++){
		bool chk = true;
		for(int j=2; j<= (int)sqrt(i); j++){
			if( i %j == 0 ){
				chk = false;
				break;
			}
		}
		if(chk) isPrime[i] =true;
	}
	
}

void generate(int c){
	if(c == n-1){
		if(isPrime[v[c]+v[c+1]]){
			for(int i=0; i<n-1; i++)
				cout << v[i] << " ";
			cout << v[n-1];
			cout << "\n";
		}
	}
	
	else{
		for(int i=2; i<=n; i++){
			if(!used[i] && isPrime[v[c]+i]){
				used[i] = true;
				v[c+1] = i;
				generate(c+1);
				used[i] = false;
			}
		}
	}
}



int main(){
	//freopen("out","w", stdout);

	generatePrime();
	
	int tt = 1;
	while(cin >> n){
		memset(used, false, sizeof used);
		v.resize(n+1);
		v[0] = 1;
		v[n] = 1; //rotation
		used[1] = true;
		if(tt > 1) cout << "\n";
		cout << "Case "<< tt <<":\n";
		tt++;
		generate(0);	
	}
	
	



	return 0;
}