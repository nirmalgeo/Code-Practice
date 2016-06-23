#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n;
	cin>>n;
	vector<long long> v,w;
	for(int i=0;i<n;i++){
		long long a;
		cin>>a;
		v.push_back(a);
	}
	
	long long max = 0;
	
	for( auto &c : v){
		if(c > max){
			w.push_back(c);
			max = c;
		}
		else
			w.push_back(max);
	}
	long long count = 1, low_value= 0;
	bool check = true;
	for(int i=1;i<n;i++){
		if(w[i] != w[i-1])
			count++;
			
		if(v[i] < v[low_value])
			low_value= i;
	}
	
	if(w[low_value] == w[n-1])
		cout << 1;
	else if(count == 1)
		cout << n;
	else
		cout<< count;
		
	//cout << "\ntest:"<< v[low_value] << " " << w[n-1];
	return 0;
}	