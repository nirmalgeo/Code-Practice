#include<bits/stdc++.h>
using namespace std;

intline int findPalinLength(string a){
	int oddcount = 0;
	int arr[26];
	memset(arr, -1, sizeof(arr));
	for(int i=0; i< a.length; i++){
		arr[a[i] - 97]++;
	}
	
	for(int i=0; i <26; i++)
		if(arr[i]&1)
			oddcount++;
	
	int l = a.length();
	
	
}
int main(){

	int t;
	cin>>t;
	while(t--){
		string a, b;
		cin >> a;
		cin >> b;
		find
		
		
	
	
	}


	return 0;
}