//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};



int main(){
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);
	
	
	freopen("B-large-practice (1).in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){
	
// code starts here 
		double C,F,X,count=2, total=0 , secs = 0;
		vector<double> time;
		cin >> C >> F >> X ;
		
		
		while(true){
			double dir = X/count;
			secs = C/count;
			//cout  << dir << " " << secs << " "<< total << "\n";
			
			if( total+dir <= ( total + secs + ( X / (count+F)))){
				total+=dir;
				break;
			}
				
			total += secs;
			count += F;
		}

		//cout << total << "\n";
		
// code ends here 

	cout << "Case #"<< cas << ": ";
	printf("%0.7lf\n", total);


	}

	return 0;
}