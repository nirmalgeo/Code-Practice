#include<bits/stdc++.h>
using namespace std;

class MedalTable{
	map<string, pair<int,pair<int,int>>> m;
	struct country
	{
		string name;
		int gold;
		int silver;
		int bronze;
		
		bool operator()( country const &a, country const &b) const {
			if(a.gold == b.gold){
				if(a.silver == b.silver){
					if(a.bronze == b.bronze){
						return b.name > a.name;
					}
					else
						return a.bronze > b.bronze;
				}
				else
					return a.silver > b.silver;
			}
			else 
				return a.gold > b.gold; 
		}	
	};
	

	public :
	
	vector <string> generate(vector <string> results){	
		for(auto &row : results){			
			string temp = "";
			int rank = 1;
			istringstream iss(row);
			
			while( iss >> temp){
				if(m.find(temp) == m.end())
					m.insert({temp, {0,{0,0}}});
				
				int g= m[temp].first;
				int s= m[temp].second.first;
				int b= m[temp].second.second;
				
				if(rank == 1) g++;
				else if(rank == 2) s++;
				else if(rank == 3) b++;
				
				m[temp] = {g, {s,b}};
				
				rank++;
			}
		}
		
		vector<country> countries;
		for(auto &c: m){
			country con;
			con.name = c.first;
			con.gold = c.second.first;
			con.silver = c.second.second.first;
			con.bronze = c.second.second.second;
			countries.push_back(con);
		}
		
	
		sort(countries.begin(), countries.end(), country());
			
		vector<string> out;
		
		for(int i=0; i< countries.size(); i++){
			string temp = "";
			temp = countries[i].name + " " + to_string(countries[i].gold) + " " + to_string(countries[i].silver) +  " " +  to_string(countries[i].bronze);
			out.push_back(temp);
		}
		return out;
	}

};