#include<bits/stdc++.h>
using namespace std;

class grafixMask{
	bool fill[600][400];
	
	public:
		int doFill(int i, int j){
			int result = 0;
			
			stack<pair<int,int>> s;
			s.push({i,j});
			
			while(!s.empty()){
				
				auto top = s.top();
				s.pop();
				
				int x = top.first;
				int y = top.second;
			
				if(x < 0 ||  x>=600) continue;
				if(y < 0 ||  y>=400) continue;
				
				if(fill[x][y]) continue;
				
				result++;
				fill[x][y] = true;
				
				s.push({x+1, y});
				s.push({x-1, y});
				s.push({x, y+1});
				s.push({x, y-1});
			}
			
			return result;
		}
	
	
		vector <int> sortedAreas(vector <string> rectangles){
			memset(fill, false, sizeof fill);
		
			for(auto &rect: rectangles){
			
				int x1, x2, y1, y2;
				
				istringstream iss(rect);
				iss >> y1 >> x1 >> y2 >> x2 ;
				cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
				
				for(int i=x1; i<=x2; i++)
					for(int j=y1; j<=y2; j++)
						fill[i][j] = true;

			}
			
			vector<int> out;
			
			for(int i=0; i<599;i++)
				for(int j=0; j<399; j++)
					if(!fill[i][j])
						out.push_back(doFill(i,j));
						
			sort(out.begin(), out.end());
			
			return out;
		}
};
