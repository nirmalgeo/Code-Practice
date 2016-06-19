#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	freopen("out","w", stdout);
	
	int cas;
	cin >> cas;

	while(cas--){
		priority_queue<int> pq;
		string load[10000], pos;
		vector<int> output;
		
		int n,t,m, temp, count;
		cin >> n >> t >> m;
		
		for(int i=0; i<m; i++)
		{
			cin >> temp >> load[i];
			pq.push(-temp);
		}
		int time = 0;
		pos = "left";
		
		for(int i=0; i<m; i++)
		{
			if(time==0) time = abs(pq.top());
		
			int count = 0;
			
			if(pos != load[i]) { pos = load[i]; time+= t; }			
			
			while(!pq.empty() && abs(pq.top()) <= time && pos == load[i]){
				count++;
				pq.pop();
				if(count == n) break;
				i++;
			}
			
			if(count == 1) i--;
			
			pos = (pos== "left")? "right": "left";
			time += t;
			
			while(count--) output.push_back(time);
		
		}	
		
		for(auto &c: output)
			cout << c << "\n";
			
		if(cas!=0) cout << "\n";
	}

	return 0;
}