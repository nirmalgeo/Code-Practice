/*
ID: nirmalg1
PROG: friday 
LANG: C++11
*/
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<tuple>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
int main()
{
	ifstream fin("friday.in");
	ofstream fout("friday.out");
	int arr[7];
	int t;
	fin>>t;
	memset(arr,0,sizeof(arr));
	int curr=0;
	FOR(i,1900,1900+t-1)
	{
		FOR(j,1,12)
		{
			arr[curr]++;
			if(j==4 || j == 9 || j==6 || j == 11)
				curr = (curr+2)%7;
		
			else if(j==2)
			{
				if(i%400==0 ||  (i%4==0 && i%100!=0))				
					curr = (curr+1)%7;
			}
			else
				curr = (curr+3)%7;	
		}
	}
	
	FOR(i,0,6)
		fout << arr[i] << " ";	
	
	return 0;
}