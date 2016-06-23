#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,b;
	int m,c;
	vector<char> v,w;
	cin>>n>>b;
	v.resize(n);
	for(int i=0;i<n;i++)
		cin>>v[i];
	
	cin>>m>>c;
	w.resize(m);
	for(int i=0;i<m;i++)
		cin>>w[i];
		
	long long num1=0, num2=0;
	for(auto &c: v){
		if( c >= 65)
			c = c - 55;
		else
			c= c - 48;
		int val = c;
		num1 = num1 + val * pow(b, --n);

	}
	
	for(auto &d: w){
		if( d >= 65)
			d = d - 55;
		else
			d= d- 48;
		int val = d; 
		num2 = num2 + val * pow(c, --m);
	}
	if(num1 == num2)
		cout << "=";
	else if(num1 < num2)
		cout << "<";
	else
		cout << ">";
	return 0;
}