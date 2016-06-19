#include<bits/stdc++.h>
using namespace std;
bitset<1000000> b;
bool assign(int start, int end){
	for(int i=start; i<end; i++){
		if(b[i]) return true;
		else b[i] = true;
	}
	return false;
}


int main(){
//	freopen("out.txt", "w" , stdout);
	int n, m;
	while(scanf("%d %d", &n, &m) && (n || m)){
		int start, end , multi;
		bool conflict = false;
		for(int i=0; i<n; i++) {
			scanf("%d %d", &start, &end);
			if(!conflict) conflict = assign(start, end);
		}
		
		for(int i=0;i <m; i++){
			scanf("%d %d %d", &start, &end, &multi);
			
			while(!conflict && start <= 1000000){
				conflict= assign(start, end);
				start += multi;
				end  += multi;
				if(start > 1000000) break;
				if(end > 1000000) end = 1000000;
			}
		}
		
		if(conflict) printf("CONFLICT\n");
		else printf("NO CONFLICT\n");
	
		b.reset();
	}
	return 0;
}
