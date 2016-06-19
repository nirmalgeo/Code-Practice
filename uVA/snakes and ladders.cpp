#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("out.txt", "w", stdout);
	int tt;
	cin>>tt;
	while(tt--){
		int a, b, c;
		cin>> a>> b>> c;
		map<int, int> m;
		int temp1, temp2;
		for(int i=0; i< b; i++){
			cin>>temp1 >> temp2;
			m.insert({temp1, temp2});
		}
		
		for(int i=1; i<=c ; i++){
			cin >> temp1;
			temp1 += 1;
			if(temp1>100) temp1 = 100;
			auto it = m.find(temp1);
			if(it != m.end())
				temp1 = it->second;
			cout <<"Position of player "<< i <<" is "<<temp1<<".\n";
		}
	}
	
	return 0;
}