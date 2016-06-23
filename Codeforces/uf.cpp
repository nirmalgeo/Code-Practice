#include<bits/stdc++.h>
using namespace std;
int main(){
	int m[5],w[5],hs,hu;
	cin>>m[0]>>m[1]>>m[2]>>m[3]>>m[4];
	cin>>w[0]>>w[1]>>w[2]>>w[3]>>w[4];
	cin>>hs>>hu;
	int val = 0;
	int temp = 500;
	for(int i=0;i<5;i++){
		float j = ((1- (float)m[i]/250)*temp - 50*w[i]);
		val  = val + max( (float)0.3*temp, (float)j); 
		temp = temp +500;
	}
	
	val = val + (hs*100) - (hu*50);
	cout << val;

	return 0;
}