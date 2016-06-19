// uva 10189
#include<bits/stdc++.h>
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int a[103][103];
int main() {
	int n,m,tt=0;
  
	while (	true) {
		cin>>n >>m;
		if(n ==0 && m==0)
			break;
		tt++;
		if(tt>1) cout<<"\n";
		char temp;

		for(int i=1;i<n+1;i++)
		{
			for(int j=1;j<m+1;j++)
			{
				cin>>temp;
				if(temp== '*')
				{
					a[i][j] =  -1;
				
					FOR(k,0,8)
					{
						if( a[i+ xarr[k]][j+ yarr[k]] != -1)
							a[i+ xarr[k]][j+ yarr[k]]++;
					}
				}
			}
		
		}
		
		cout << "Field #"<<tt<<":\n";	
		FOR(i,1,n+1)
		{
			FOR(j,1,m+1)
			{
				if(a[i][j] == -1)
					cout<<'*';
				else
					cout <<a[i][j];
			}
			cout<<"\n";
		}
		
	}
	return 0; 
}
