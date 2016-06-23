#include<bits/stdc++.h>
using namespace std;
int arr[100005];
int main(){
	int n;
	scanf("%d", &n);
	arr[1] = 1;
	int j=2;
	for(int i=2; i<=n; i++){
		arr[j] = 1;
		while(j>=2 && arr[j-1] == arr[j]){
			arr[j-1]++;
			arr[j] = 0;
			j--;
		}
		
		if(arr[j]!=0)
			j++;
	}
	
	for(int i=1; i<j; i++)
		cout <<arr[i] << " ";

	return 0;
}