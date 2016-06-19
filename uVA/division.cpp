// uva 725
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n;
	bool printed = false;
	while(scanf("%d",&n) && n){
		bool found = false;
		if(printed)
			cout << "\n";
		for(int fghij=1234; fghij<=98765; fghij++){
			int abcde = fghij * n;
			if(abcde > 100000)
				continue;			
			int tmp =abcde, used = (fghij < 10000);
			while(tmp) { used|= 1 << (tmp%10); tmp/=10;}
			tmp = fghij;
			while(tmp) { used|= 1 << (tmp%10); tmp/=10;}
			if(used == ( (1 << 10)-1)){
				printf("%0.5d / %0.5d = %d\n", abcde, fghij, n);
				found = true;
			}
		}
		
		if(!found)
			printf("There are no solutions for %d.\n", n);
			
		printed = true;
	}


	return 0;
}