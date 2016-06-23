#include<bits/stdc++.h>
#define inf (ull) 120
using namespace std;
typedef unsigned long long ull;

vector<ull> v;
ull num=1;
ull cnt = 1;

void precalc(){
	
	v.push_back(0);
	cnt = 1;
	while(cnt < inf){
		
		ull temp = num;
		bool flag = true;
		
		while(temp){
			ull mod = temp%10;
			if(mod%2){
				flag = false;
				break;
			}
			temp/=10;
		}
		
		if(flag){
			v.push_back(num);
			cnt++;
		}
		num++;
	}
	
	int i=0;
	for(auto &c: v){
		cout << c <<" " << i++ <<"\n";;
	}
	getchar();
}

int main(){
	precalc();

	ull t, k;
	cin >> t;
	
	while(t--){
		cin >> k;
		cout << v[k-1] << "\n";
	}
	return 0;
}