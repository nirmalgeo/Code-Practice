#include<bits/stdc++.h>
using namespace std;


class BusinessTasks{

	public :
		string getTask(vector <string> list, int n){
			
			auto it = list.begin();
			while(list.size() > 1){
				for(int i=1; i<n; i++){
					it++;
					if(it == list.end()) it = list.begin();
				}
				
				it = list.erase(it);
				if(it == list.end()) it = list.begin();
			}
			return list[0];
		}
};