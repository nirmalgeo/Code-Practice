#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<b;i++)

using namespace std;
int main(){
	int n;
	cin>>n;
	assert(n>=1 && n<=100);
	queue<int> gi,id;
	//queue<int>::iterator it;
	FOR(i,0,n){
		int a;
		cin>>a;
		//assert(gi.find(a) != gi.end());
		gi.push(a);
	}
	
	FOR(i,0,n){
		int a;
		cin>>a;
		//assert(id.find(a) != id.end());
		id.push(a);
	}
	int count = 0;
	while(!gi.empty()){
		if(gi.front() == id.front()){
			count++;
			gi.pop();
			id.pop();
		}
		else{
			count++;
			int curr = gi.front();
			gi.pop();
			gi.push(curr);
		}
	}
	
	cout << count;
	return 0;
}