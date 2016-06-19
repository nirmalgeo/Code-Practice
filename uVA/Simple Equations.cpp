#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int A,B,C;
		scanf("%d %d %d", &A, &B, &C);
		bool found= false;
		for(int x=-100 ; x<=100 ; x++)
			for(int y=-100; y<=100 ; y++)
				for(int z=-100; z<=100; z++)
					if( x!=y && y!=z && x!=z && x+y+z==A && x*y*z==B && x*x + y*y + z*z ==C){
							if(!found)
								printf("%d %d %d\n", x, y, z);
						found = true;
					}
		if(!found)
			printf("No solution.\n");
	
	}
	return 0;
}