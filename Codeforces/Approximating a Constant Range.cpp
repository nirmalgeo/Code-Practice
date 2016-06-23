#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005];
int main(){
	int n;
	cin>>n;
	assert(n>=2 && n<=100000);
	vector<int> v;
	v.resize(n);
	for(int i=0;i<n;i++)
		cin>>v[i];
	
	a[0] = 0;
	int count = 1;
	int max=1;
	for(int i=1;i<n;i++){
		a[i] = v[i] - v[i-1];
	}
	b[0]=1;
	max = b[0];
	for(int i=1;i<n;i++){
		if(a[i] + a[i-1] <= 1)
			b[i] = b[i-1] + 1;
		else
			b[i] = 2;
		
		if(b[i] > max)
			max = b[i];
	}
	
	for(int i=0;i<n;i++)
	{
		cout<<v[i] << " " << a[i] << " " << b[i] <<"\n";
	}
	

cout << max;


	return 0;
}