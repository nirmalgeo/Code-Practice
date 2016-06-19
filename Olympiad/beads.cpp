/*
ID: nirmalg1
PROG: beads 
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

string process(string str, int n){
	string temp = "";
	
	temp += str.substr(n);
	if( n != 0) temp+= str.substr(0,n);
	
	return temp;
}

int countnum(string str){
	int sum = 0;
	char ch;
	
	for(int i=0; i<str.length(); i++){
		if(str[i] == 'w')
			sum++;
		else{	
			ch = str[i];
			for(int j=i; j<str.length(); j++){
				if(str[j] == ch || str[j] == 'w')
					sum++;
				else 
					break;
			}
			return sum;
		}
	}

}

int count(string str){
	int forward = 0, backward = 0;
	forward = countnum(str);
	reverse(str.begin(), str.end());
	backward = countnum(str);
	//cerr << forward << " " << backward <<  " " << str << "\n";
	int ans = forward + backward;
	if(ans > str.length()) ans = str.length();
	return ans;
}


int main()
{
	freopen("beads.in" , "r" , stdin);
	freopen("beads.out", "w" , stdout);
	
	int n;
	cin >> n;
	string s;
	cin >> s;
	int ans = 0;
	for(int i=0; i<s.length(); i++){
		string str = process(s, i);
		int temp = count(str);
		ans = max(temp, ans);
	}
	
	cout << ans << "\n";
	
	return 0;
}