/*
ID: nirmalg1
PROG: dualpal 
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


char value[] = {'0', '1', '2','3','4','5','6','7','8','9'};

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

	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);

	int n, s;
	cin >> n >> s;
	s++;
	for(;;){
		string temp;
		int count = 0;
		for(int i=2; i<=10; i++){
			temp = base( s, i );
			if(palindrome(temp)){
				count++;
			}
			if(count == 2) break;
		}
		
		if(count == 2) {
			cout << s << "\n";
			n--;
		}
		if(n == 0) break;
		s++;
	}
	
	
	
	return 0;
}