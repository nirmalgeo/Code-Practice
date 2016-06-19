#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int f,r;
	vector<int> front, rear;
	while(true){
		cin >> f;
		if( f==0 ) break;
		
		cin >> r;
		
		front.resize(f);
		rear.resize(r);
		
		for(int i=0; i< f; i++) cin>> front[i];
		for(int i=0; i< r; i++) cin >> rear[i];
		
		vector<double> out;
		
		for(int i=0;i<r; i++){
			for(int j=0; j<f; j++){
				double temp = (double) rear[i] / (double) front[j];
				out.push_back(temp);
			}
		}
		
	
		int sz = out.size();
		
		double ans = -1;
		
		sort(out.begin(), out.end());
		
		for(int i=0; i< sz -1; i++)
			ans = max(ans, out[i+1]/out[i]);
		
	
		printf("%0.2lf\n", ans);
	
	}


	return 0;
}