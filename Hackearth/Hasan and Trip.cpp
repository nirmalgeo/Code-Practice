#include<bits/stdc++.h>
using namespace std;
vector<int> x,y,f;
set<int,int,int> s;
int main(){
	int n;
	cin>>n;
	x.resize(n);
	y.resize(n);
	f.resize(n);
	for(int i=0;i<n;i++){
		cin>> x[i] >> y[i] >> f[i];
		s.insert(make_pair(x[i],y[i],i));
	}
	double val = 0;
	for(int i=0;i<n;i++){
	
	
	}
	
	return 0;
}