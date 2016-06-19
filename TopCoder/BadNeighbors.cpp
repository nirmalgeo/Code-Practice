#include<bits/stdc++.h>
using namespace std;
class BadNeighbors{
	public:
		int maxDonations(vector <int> donations){
			int l , r;
			l = r = 0;
			int n = donations.size();
			
			for(int i=0; i< n-1; i+=2) 
				l+= donations[i];
			for(int i=1; i< n; i+=2)
				r+= donations[i];
				
			int ans = max(l, r);
			return ans;
		
		}

};