#include<bits/stdc++.h>
using namespace std;
 
string input;
map <string, bool> m;
 

 
int main ()
{
	int t;
	scanf("%d",&t);
    while ( t-- ) {
		cin >> input;
        m.clear ();
		string temp = "";
		int count = 0;
		for(int i=0; i< input.length(); i++){
			temp += input[i];
			if(m.find(temp) == m.end()){
				m.insert({temp,true});
				temp = "";
				count++;
				continue;
			}
			if(count == 3){
				temp = input.substr(i,input.length()-1);
				if(m.find(temp) == m.end()){
					m.insert({temp, true});
					temp = "";
					count++;
					break;
				}
			}
		}
		
		if(count == 4)
			printf("YES\n");
		else
			printf("NO\n");
		
	}
 
    return 0;
}