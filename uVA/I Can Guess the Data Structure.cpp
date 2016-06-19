#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	while(scanf("%d",&n) != EOF){
		bool stackTest = true, queueTest = true, priority_queueTest= true;
		stack<int> s;
		queue<int> q;
		priority_queue<int> pq;
		int temp;
		for(int i=0; i<n; i++){
			scanf("%d",&temp);
			if(temp == 1){
				scanf("%d", &temp);
				s.push(temp);
				q.push(temp);
				pq.push(temp);
			}
			else{
				scanf("%d",&temp);
				if(s.empty() || s.top() != temp)
					stackTest = false;
				if(q.empty() || q.front() != temp)
					queueTest = false;
				if(pq.empty() || pq.top() != temp)
					priority_queueTest = false;
				
				if(!s.empty())
					s.pop();
				if(!q.empty())
					q.pop();
				if(!pq.empty())
					pq.pop();
			
			}
		}
				
			if(!stackTest && !queueTest && !priority_queueTest)
				printf("impossible\n");
			else if(stackTest && !queueTest && !priority_queueTest)
				printf("stack\n");
			else if(queueTest && !stackTest && !priority_queueTest)
				printf("queue\n");
			else if(!queueTest && !stackTest && priority_queueTest)
				printf("priority queue\n");
			else
				printf("not sure\n");

	}
	return 0;
}