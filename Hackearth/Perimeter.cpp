#include<bits/stdc++.h>
using namespace std;
int main(){
	int m,n;
	cin>>m>>n;
	char a[1005][1005];
	int counti = m;
	int countj = n;
	for(int i=1;i<=m;i++){
		for(int j=1; j<=n; j++){
			cin>>a[i][j];
			if(a[i][j] == 'x'){
				counti--;
				countj--;
			}
		}
	}
	
	if( counti>0 && countj>0)
		cout << 2*(counti-1) + 2*(countj-1)<<"\n";
	else
		cout << "impossible"<<"\n";
	
	cerr<<counti << "  "<< countj ;


	return 0;
}