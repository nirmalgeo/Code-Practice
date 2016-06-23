#include<bits/stdc++.h>
using namespace std;
int A[1000000], B[1000000];
int main(){
	
	bool first= false;
	bool found= false;
	int num, ind=0;
	char ch;
	int cnt1=0, cnt2=0;
	while((ch = getchar())!= '\n'){
	
		num = (int) ch - 48;
		if(num!=0)
			first = true;
		if(!first)
			continue;
		
		A[ind++] = num;
		cnt1++;
	}
	
	first = false;
	ind=0;
	while((ch = getchar())!= '\n'){
	
		num = (int) ch - 48;
		if(num!=0)
			first = true;
		if(!first)
			continue;
		B[ind++] = num;
		cnt2++;
	}
	
	//rr <<cnt1 << " " << cnt2<<"\n";
	
	if(cnt1 < cnt2){
		printf("<");
	}
	else if(cnt1 > cnt2){
		printf(">");
	}
	
	else {
		found = true;
		for(int i=0; i< cnt1; i++){
			//rr << A[i] << " " << B[i];
			if(A[i] == B[i])
				continue;
			else if(A[i] > B[i]){
				printf(">");
				found = false;
				break;
			}
			else{
				printf("<");
				found = false;
				break;
			
			}
		}
		
		if(found)
			printf("=");
	}

	return 0;
}
