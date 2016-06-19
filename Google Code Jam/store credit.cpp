//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
	int c, l;
	vector<int> items;
	cin >> c;
	cin >> l;
	items.resize(l);
	for(int i=0;i <l; i++)
		cin >> items[i];
	bool found = false;
	for(int i=0; i<l; i++){
		for(int j=0; j <l; j++){
			if(i!=j && items[i]+items[j] == c){
				cout << "Case #"<< cas << ": "<< i+1 << " " << j+1 <<"\n";
				found = true;
				break;
			}
		}
		if(found) break;
	}

// code ends here 

	
	
	}

	return 0;
}