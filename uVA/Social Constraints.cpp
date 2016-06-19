#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	int arr[8] = {0,1,2,3,4,5,6,7};
	
	while(scanf("%d %d",&n, &m) && (n || m)){
		int totalcount =0;
		int constraintcount=0; 
		int a,b,c;
		int f1[21], f2[21], f3[21];
		for(int ii=0; ii<m; ii++){
			scanf("%d %d %d", &f1[ii] , &f2[ii], &f3[ii]);
		}

		do{				
			totalcount++;
			int posA, posB;
			for(int idx=0; idx<m; idx++){
				for(int ii=0; ii<n; ii++){
					a = f1[idx];
					b = f2[idx];
					c = f3[idx];
					if(arr[ii] ==  a)
						posA = ii;
					if(arr[ii] == b)
						posB= ii;
				}
			
				if((c < 0 &&   abs(posA - posB) >= abs(c)) || ( c >=0 && abs(posA- posB) <= c))
					constraintcount++;
			}
		}while(next_permutation(arr, arr+n));
		
		if(m == 0)
			printf("%d\n",totalcount);
		else
			printf("%d\n", constraintcount);
	}
	return 0;
}