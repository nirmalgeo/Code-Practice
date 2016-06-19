#include<bits/stdc++.h>
using namespace std;
vector<char> v;
int n,q;
int BIT[100010][26];
void update(int x, int val,int ind){
	for(;x<=n; x+=(x&-x)){
		BIT[x][ind] += val;
	}
}

int query(int x, int ind){
	int ans = 0;
	for(;x>=1; x-=(x&-x)){
		ans += BIT[x][ind];
	}
	return ans;
}

int main(){

	cin>>n>>q;
	v.resize(n+1);
	
	for(int i=1;i<=n;i++){
		cin>>v[i];
		//cout << v[i] - 'a' ;
		update(i,1,v[i]-'a');
		//cout << query(i, v[i]-'a');
	}
	while(q--){
		int a;
		cin>>a;
		if(a == 1){
			int pos;
			char ch;
			cin>>pos>>ch;
			update(pos,1, ch-'a');
			update(pos,-1, v[pos]-'a');
			v[pos]= ch;
		}		
		else{
			int posi, posj;
			cin>>posi>>posj;
			int odd = 0;
			int count =0;
			for(int i=0;i<26;i++){
				odd = query(posj,i) - query(posi-1,i);
				//cout << query(posj,i) << "  "<< query(posi-1,i) << " " << odd<<"\n";
				if(odd%2)
					count++;
			}
			//cout << count <<"\n";
			
			if(count <=1)
				cout << "yes\n";
			else
				cout<<"no\n";
		}
	}
	return 0;
	
}