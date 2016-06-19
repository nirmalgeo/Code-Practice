/*
ID: nirmalg1
PROG: milk2 
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
bool dp[1000000];

int main(){

	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);
	
	int n;
	cin >> n;
	
	int start[n] , end[n];
	int startTime = 1000000, endTime = 0;
	for(int i=0; i<n; i++){
		cin >> start[i] >> end[i];
		if(start[i] < startTime)
			startTime = start[i];
		if(end[i] > endTime)
			endTime = end[i];
	}

	for(int i=0; i<n; i++){
		for(int j=start[i]; j < end[i]; j++)
			dp[j] = true;
	}
		
	int maxMilk = 0 , maxNoMilk = 0;
	int tempMilk = 0, tempNoMilk = 0;
	for(int i= startTime; i< endTime; i++){
		if(dp[i]){
			tempNoMilk=0;
			tempMilk++;
		}
		else{
			tempMilk = 0;
			tempNoMilk++;
		}
	
		maxMilk = max(tempMilk, maxMilk);
		maxNoMilk = max(tempNoMilk, maxNoMilk);
	}
	cout << maxMilk << " " << maxNoMilk << "\n";
	
	return 0;
}