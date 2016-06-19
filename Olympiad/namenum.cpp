/*
ID: nirmalg1
PROG: namenum 
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


int main(){

	freopen("namenum.in", "r", stdin);
	freopen("namenum.out", "w", stdout);

	ifstream fileInput("dict.txt");
	string temp;
	
	string in;
	cin >> in;
	
	bool found = false;
	while(fileInput >> temp){
		string result = "";
		for(int i=0; i< temp.length(); i++){
			if(temp[i] == 'A' || temp[i] == 'B' || temp[i] == 'C')
				result += "2";
			else if(temp[i] == 'D' || temp[i] == 'E' || temp[i] == 'F')
				result += "3";
			else if(temp[i] == 'G' || temp[i] == 'H' || temp[i] == 'I')
				result += "4";
			else if(temp[i] == 'J' || temp[i] == 'K' || temp[i] == 'L')
				result += "5";
			else if(temp[i] == 'M' || temp[i] == 'N' || temp[i] == 'O')
				result += "6";
			else if(temp[i] == 'P' || temp[i] == 'R' || temp[i] == 'S')
				result += "7";
			else if(temp[i] == 'T' || temp[i] == 'U' || temp[i] == 'V')
				result += "8";
			else if(temp[i] == 'W' || temp[i] == 'X' || temp[i] == 'Y')
				result += "9";
		}
		
		if(result == in){
			cout << temp << "\n";
			found = true;
		}
	}
	
	if(!found)
		cout << "NONE\n";

	
	return 0;
}