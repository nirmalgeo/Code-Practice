/*
ID: nirmalg1
PROG: milk 
LANG: C++11
*/
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<tuple>
#include<algorithm>
#include<map>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FORR(i,a,b) for(int i=a; i>=b;i--)
#define INF 700
using namespace std;
typedef long long ll;



int main(){

	freopen("milk.in", "r", stdin);
	freopen("milk.out", "w", stdout);

	int n, m;
	cin >> n >> m;
	
	vector<pair<int, int>> milk;
	for(int i=0; i<m; i++){
		int price, unit;
		cin >> price >> unit;
		
		milk.push_back({price, -1*unit});
	}
	
	int cost = 0;
	
	sort(milk.begin(), milk.end());
	
	
	for(int i=0; i< milk.size(); i++){
		int currStock = milk[i].second * -1;
		
		if(currStock >= n)
			currStock = n;
		
		cost += (currStock*milk[i].first);
		
		n-= currStock;
	
		if(n == 0) break;
	}
	
	cout << cost << "\n";
		
	return 0;
}