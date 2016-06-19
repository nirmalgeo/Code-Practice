//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int n;
		cin >> n;
		double temp;
		priority_queue<double> naomi, ken , c1, c2;
		
		for(int i=0; i<n; i++) { cin >> temp; naomi.push(temp);}
		for(int i=0; i<n; i++) { cin >> temp; ken.push(temp);}
		
		
		int war = 0, deciet = 0;
		
		c1 = naomi;
		c2 = ken;
		
		while(!naomi.empty() && !ken.empty()){
			if(naomi.top() > ken.top())
				war++;
			naomi.pop();
			ken.pop();
		}


// code ends here 

	cout << "Case #"<< cas << ": "<< deciet << " " << war <<"\n";


	}

	return 0;
}