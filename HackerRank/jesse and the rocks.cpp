#include<bits/stdc++.h>
using namespace std;
vector<int> v, dp;
int main(){
	long long n, strengthJesse, temp, count =0;
	cin>> n >> strengthJesse;
	int skip = 0;
	for(int i=0; i<n ; i++){
		cin>>temp;
		if(temp > strengthJesse)
			skip++;
			
		if(temp <= strengthJesse && skip <=1)
			count++;
		
	}
	
	cout << count ;

	return 0;
}