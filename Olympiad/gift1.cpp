/*
ID: nirmalg1
PROG: friday 
LANG: C++11
*/
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<tuple>
#define FOR(i,a,b) for(int i=a;i<b;i++)
using namespace std;
typedef long long ll;


int returnAmount(string a, vector<pair<string,int>> v)
{
	for(auto &c: v)
	{
		if( c.first== a)
			return c.second;	
	}
}

void changeAmount(string a, vector<pair<string,int>> &v, int b)
{
	for(auto &c: v)
	{
		if(c.first == a)
		{
			c.second += b;
			return;
		}
	}
}

int main()
{
	ifstream fin("friday.in");
	ofstream fout("friday.out");
	string a,b;
	int init, count;
	int t;
	fin>>t;
	vector<pair<string,int>> v,w;
	
	FOR(i,0,t)
	{	
		fin>>a;
		//v.push_back({a,0});
		w.push_back({a,0});
	}
		
	FOR(i,0,t)
	{
		fin>>a;
		fin>>init>> count;
		//fout << a << " "<< init << " " << count<<endl;
		//changeAmount(a,v,init);
		int temp=0;
		if(count!=0)
		  temp = init/count;
	
		FOR(j,0,count)
		{
			fin>>b;
			changeAmount(b,w,temp);
		}
		changeAmount(a,w, -(temp*count));
	}
	
	for(auto &c:w)
		fout<<c.first<<" "<< c.second << endl;
	return 0;
}