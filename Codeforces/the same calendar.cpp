#include<bits/stdc++.h>
using namespace std;
int main(){

	int y;
	cin >> y;
	int temp = y;
	if(temp%400==0 || ( temp %4==0 && temp%100!=0))
		temp +=28;
	else{
		int mod=0;
		if(temp%400 < 4)
			mod = temp%400;
		else 
			mod = temp%4;

		if(mod == 1)	temp+=6;
		else temp+=11;
	}
		cout << temp;


	return 0;
}