/*
ID: nirmalg1
PROG: transform 
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

char before[11][11];
char after[11][11];
int n;

bool option1(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(before[i][j] != after[j][n-i+1])
				return false;
	return true;
}

bool option2(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(before[i][j] != after[n-i+1][n-j+1])
				return false;
	return true;
}

bool option3(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(before[i][j] != after[n-j+1][i])
				return false;
	return true;
}

bool option4(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(before[i][j] != after[i][n-j+1])
				return false;
	return true;
}


bool option5(){
	
	char temp[11][11] = {0};
	
	
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			temp[i][j] = before[i][j];

	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			before[i][n-j+1] = temp[i][j];
	
	
	if( option1() || option2 () || option3())
		return true;
		
	return false; 
}


bool option6(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(before[i][j] != after[i][j])
				return false;
	return true;
}



int main(){

	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);


	cin >> n;
	
	for(int i=1; i<=n ;i++)
		for(int j=1; j<=n ; j++)
			cin >> before[i][j];
	
	for(int i=1; i<=n ;i++)
		for(int j=1; j<=n ; j++)
			cin >> after[i][j];	
	
	
	if(option1())
		cout << "1\n";
	else if(option2())
		cout << "2\n";
	else if(option3())
		cout << "3\n";
	else if(option4())
		cout << "4\n";
	else if(option5())
		cout << "5\n";
	else if(option6())
		cout << "6\n";
	else
		cout << "7\n";
	
	
	
	
	return 0;
}