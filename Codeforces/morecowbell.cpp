#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n, k;
	cin>> n >>k;
	
	vector<long long> v;
	v.resize(n);
	for(int i=0;i<n;i++)
		cin>>v[i];

	vector<long long> w;
	w.resize(n);
	w[0] = v[0];
	w[1] = v[1];
	long long maxVal;
	if(n>2){
		for(int i=2;i<n;i++){
			w[i] = max( v[i-1] + v[i-2] , v[i]);	
		}
		maxVal = w[0];
		for(int i=0;i<n;i++){
			if(w[i]> maxVal)
				maxVal = w[i];

		}
	}
	else
	{
		maxVal=0;
		for(auto &c:v)
			maxVal += c;
	}
	cout << maxVal ;
	return 0;
}