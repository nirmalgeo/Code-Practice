#include<bits/stdc++.h>
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tt;
	cin >> tt;
	
	while(tt--){
		int count = 0;
		int l,m;
		cin >> l >> m;
		
		queue<int> left, right;
		int temp;
		
		string posi, pos="left";
		for(int i=0; i<m; i++){
			cin >> temp >> posi;
			if(posi == "left") left.push(temp);
			else right.push(temp);	
		}
	
		double val=0, cur=0;
		while(true){
			//cout << count << " " << val << "\n";
		
			if(left.empty() && right.empty()) break;
			
			if(pos == "left" && left.empty()) { pos = "right"; count++; val=0; continue; }
			else if(pos == "right" && right.empty()) { pos = "left"; count++; val=0; continue; }
			
			
			if(pos == "left" && !left.empty())
				cur = (double) left.front()/100;
				
			else if(pos == "right" && !right.empty())
				cur = (double) right.front()/100;
			
			
			if((val + cur ) >= l) 
			{ 
				pos = (pos == "left")? "right": "left";
				val =0;
				count++; 
				continue;
			} 	
				
			val += cur;
			if(pos == "left")	 left.pop();
			else	right.pop();
		}
		
		count++;
		cout << count << "\n";
	
	}



	return 0;
}