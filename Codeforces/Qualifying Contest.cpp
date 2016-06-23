#include<bits/stdc++.h>
using namespace std;

typedef struct {
	string name;
	int id;
	int score;
}team;

typedef struct{
	string name;
	int count ;
	int id;
}regionteam;

bool cmp(team a, team b){
	
	if(a.id != b.id)
		return a.id <= b.id;
	
	if(a.id == b.id && a.score != b.score)
		return a.score > b.score;		
	
	else
		return a.name <= b.name;
}

int main(){
	
	int n,m;
	cin >> n >> m;
	
	vector<team> v;
	
	for(int i=0; i< n; i++)
	{
		team a;
		cin >> a.name >> a.id >> a.score;
		v.push_back(a);
	}

	sort(v.begin(), v.end(), cmp);
	

	string name= "";
	int k=0; 
	int lastid = -1;
	vector<team>::iterator it = v.begin();
	bool prnt = false;
	
	for(auto &c: v){	
		if(lastid != c.id) { lastid = c.id; k=0; name = ""; }
		if(k < 2 ) { name += c.name; k++; if(k<2) name += " "; }
		
		int ind = it - v.begin();
		if(k == 2) { 
			if ( (*(it+1)).id == c.id &&  (*(it+1)).score == c.score) name = "?";
			cout << name << endl;
			k++;
		}
	
		it++;
	}
	
	
	return 0;
}