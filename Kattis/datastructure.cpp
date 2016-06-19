#include<bits/stdc++.h>
using namespace std;
int main(){

	int n;
	while(scanf("%d",&n)==1){
		assert(n>=1 && n<=1000);
		int pqFlag =0, qFlag =0, sFlag= 0;
		int count = 0;
		priority_queue<int> pq;
		queue<int> q;
		stack<int> s;
		while(n--){
			
			int t,x;
			scanf("%d %d",&t,&x);
			assert(t==1 || t==2);
			assert(x>=0 && x<=100);
			


			if(t==1){
				pq.push(x);
				q.push(x);
				s.push(x);
			}
			else{
				if(!pq.empty() && pq.top() == x){
					//cerr<<"pq";
					pqFlag++;
				}
				if(!q.empty() && q.front() == x){
					//cerr<<"queue";
					qFlag++;
				}
				
				if(!s.empty() && s.top() == x){
					//cerr<<"stack";
					sFlag++;
				}
				if(!pq.empty())
					pq.pop();
				if(!q.empty())
					q.pop();
				if(!s.empty())
					s.pop();
				count++;
			}
		}
		if(!sFlag && !qFlag && !pqFlag)
			cout<<"impossible\n";
		else if(sFlag == count && qFlag!=count && pqFlag!=count)
			cout<<"stack\n";
		else if(qFlag == count && sFlag!=count && pqFlag!=count)
			cout << "queue\n";
		else if( pqFlag == count && sFlag!=count && qFlag!=count)
			cout <<"priority queue\n";
		else
			cout<<"not sure\n";
			
		//cerr<< pqFlag << " " << sFlag << " " << qFlag << " " <<count << "\n";
	}
	return 0;
}