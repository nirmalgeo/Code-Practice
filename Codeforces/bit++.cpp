#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int n;
	cin >> n;
	
	int x=0;
	string temp;
	while(n--){
		cin >> temp;
		
		if(temp[0] == '+' || temp[temp.length()-1] == '+')
			x++;
		else
			x--;
	}
	cout << x ;

	return 0;
}