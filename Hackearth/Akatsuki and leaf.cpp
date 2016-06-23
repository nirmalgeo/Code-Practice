#include<bits/stdc++.h>
#define INF LLONG_MAX;
using namespace std;

vector<pair<int, int>> aka, leaf;
long long dp[25][25];

long long calc(int x , int y){
	return (abs(aka[x].first - leaf[x].first) + abs(aka[y].second - leaf[y].second));
}

int main(){

	int n, x, y;
	cin >> n;
	memset(dp, -1, sizeof dp);
	
	for(int i=0; i<n; i++)	{
		cin >> x >> y;
		aka.push_back({x, y});
	}

	for(int i=0; i<n; i++) {
		cin >> x >> y;
		leaf.push_back({x, y});
	}
	
	sort(aka.begin(), aka.end());
	sort(leaf.begin(), leaf.end());
	
	long long sum = 0;
	
	for(int i=0; i<n; i++)
		sum += calc(i, i);
		
	cout << sum;

	return 0;
}