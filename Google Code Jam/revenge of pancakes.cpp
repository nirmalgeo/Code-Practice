//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("B-large.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	
	for(int cas =1; cas <= cases; cas++){
	
// code starts here 
		string str, comp = "";
		cin >> str;
		for(int i=0; i< str.length(); i++)
			comp += "+";
		
		int ans = 0;
		
		while(true){
			char ch = (str[0] == '+')? '-' : '+';
			if(str == comp) break;
			for(int i=0; i<str.length();i++){
				if(str[i] != ch)
					str[i] = ch;
				else
					break;
			}
			ans++;
		}
// code ends here 

	cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}