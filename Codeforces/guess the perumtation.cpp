#include<bits/stdc++.h>
using namespace std;

int perm[51];
int arr[51][51];
int main(){
	for(int i=1; i<=50; i++)
		perm[i] = i;
	
	int n, tempi, tempj;
	scanf("%d", &n);
	for(int i=0; i< n; i++)
		for(int j=0; j<n; j++)
			scanf("%d", &arr[i][j]);
			
	int temp ;
	for(int j=0; j<n; j++){
		bool found = true;
		for(int i=0; i<n; i++){
			if(arr[i][j] == 1 || arr[i][j] == 0)
				continue;
			else {
				found = false;
				break;
			}
		}
		if(found == true){
			temp = j;
			break;
		}
	}
	
	perm[temp] = 1;
	
	
	
	
	
}