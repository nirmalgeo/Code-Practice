#include<bits/stdc++.h>
#define REPP(i,a ,b) for(int i=a; i<=b; i++)
using namespace std;

class PathFinding{
	
	class node{
		public:
		int Ax, Ay, Bx, By;
		int steps;
		
	};
	
	bool visited[20][20][20][20];
	int steps;
	public: 
		
		void findChar(vector<string> board, char ch, pair<int, int> &t){
			int x=0;
			for(auto &cell : board){
				auto it = find(cell.begin(), cell.end(), ch);
				if(it == cell.end())
				{
					x++;
					continue;
				}
				else{
					t.first = x;
					t.second = it - cell.begin();
					return ;
				}
			}
		}
	
		int minTurns(vector <string> board){
			memset(visited, false, sizeof visited);
			
			int xMax = board[0].length();
			int yMax = board.size();
			pair<int, int> A;
			
			node start;
			findChar(board, 'A', A);
			start.Ax = A.first;
			start.Ay = A.second;
			findChar(board, 'B', A);
			start.Bx = A.first;
			start.By = A.second;
			
			start.steps = 0;
			
			queue<node> q;
			q.push(start);
			visited[start.Ax][start.Ay][start.Bx][start.By] = true;
		
			while(!q.empty()){
				auto top = q.front();
				q.pop();
				
				if(top.Ax < 0 || top.Ax >= xMax) continue;
				if(top.Ay < 0 || top.Ay >= yMax) continue;
				if(top.Bx < 0 || top.Bx >= xMax) continue;
				if(top.By < 0 || top.By >= yMax) continue;
			
				if(top.Ax == start.Bx && top.Ay == start.By && top.Bx == start.Ax && top.By == start.Ay)
					return top.steps;
				
				REPP(Axdelta, -1, 1) REPP(Aydelta, -1, 1) REPP(Bxdelta, -1, 1) REPP(Bydelta, -1 , 1){
					if(top.Ax == top.Bx + Bxdelta && top.Ay == top.By + Bydelta && 
						top.Bx == top.Ax + Axdelta && top.By == top.Ay + Aydelta)
							continue;
					
					node temp;
					temp.Ax = top.Ax +Axdelta;
					temp.Ay = top.Ay +Aydelta;
					temp.Bx = top.Bx +Bxdelta;
					temp.By = top.By +Bydelta;
					temp.steps = top.steps + 1;
					
					if(top.Ax < 0 || top.Ax >= xMax) continue;
					if(top.Ay < 0 || top.Ay >= yMax) continue;
					if(top.Bx < 0 || top.Bx >= xMax) continue;
					if(top.By < 0 || top.By >= yMax) continue;
					
					if(!visited[temp.Ax][temp.Ay][temp.Bx][temp.By]){
						visited[temp.Ax][temp.Ay][temp.Bx][temp.By] = true;
						q.push(temp);
					}
				}
			}
			return -1;
		}
};