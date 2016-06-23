#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a ,b;
	cin>> a>>b;
	int small;
	if(a<b)
		small =a;
	else
		small =b;
	
	int c =  abs(a-b);
	c = c/2;
	cout << small << " " << c;
	return 0;
}