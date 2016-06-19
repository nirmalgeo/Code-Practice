#include<iostream>
#include<algorithm>
using namespace std;
int main(){

	int arr[] {1,2,3,4,5};
	
	do {
	
		for(int i=0; i<5; i++) cout << arr[i]  << " ";
		cout <<endl;
	}while(next_permutation(arr, arr+5));
	
	return 0;
}