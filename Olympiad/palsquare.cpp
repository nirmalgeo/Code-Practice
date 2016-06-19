/*
ID: nirmalg1
PROG: palsquare 
LANG: C++11
*/
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<tuple>
#include<algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FORR(i,a,b) for(int i=a; i>=b;i--)
#define INF 700
using namespace std;
typedef long long ll;


char value[] = {'0', '1', '2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I'};

string base(int num , int base){
	string temp = "";
	
	while(num != 0){
		temp = value[num%base] + temp;
		num /= base;
	}

	return temp;
}

bool palindrome(string temp){
	
	for(int i=0; i < temp.length()/2; i++)
		if( temp[i] != temp[temp.length() - 1  - i])
			return false;
	return true;
}


int main(){

	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);

	int b;
	cin >> b;
	
	for(int i=1; i<= 300; i++){
		string sq = base( i* i , b);
		
		if( palindrome(sq) ){
			string val = base( i , b );
			cout << val << " " << sq << "\n";
		}
	}
	
	
	return 0;
}