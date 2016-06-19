// uva 10945
#include<bits/stdc++.h>
using namespace std;
int main(){
	string x;
	while(1){
		getline(cin,x);
		if( x == "DONE")
			break;
			
		string forwardstring = "";
		
		for(int i=0 ; i < x.length(); i++){
			if(!(x.at(i) == ' ' || x.at(i) == '.' || x.at(i) == ',' || x.at(i) == '!' || x.at(i) == '?')){
				if(x.at(i)>=65 && x.at(i) <= 90)
					x[i] = x[i] + 32;
				
				forwardstring += x[i];
			}
			
		}
		
		string reversestring = forwardstring;
		
		reverse(reversestring.begin(), reversestring.end());
		
		if(forwardstring == reversestring)
			printf("You won't be eaten!\n");
		else
			printf("Uh oh..\n");
	}

	return 0;
}