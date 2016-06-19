#include<bits/stdc++.h>
using namespace std;
bool b[26], g[26], wrong[26];
inline bool checkifWon(){
	for(int i=0; i<26; i++)
		if(b[i] != g[i])
			return false;
			
	return true;
}

int main(){
	int test;
	//freopen("out.txt", "w", stdout);
	while(scanf("%d", &test) && test!= -1){
		string in, out;
		cin>> in;
		cin>> out;

		cout << "Round "<< test<< "\n";
		memset(b, false, sizeof(b));
		memset(g, false, sizeof(g));
		memset(wrong, false, sizeof(wrong));
		int uniqueCount=0, wrongCount = 0;
		for(int i=0; i< in.size(); i++){
			int val = in[i] - 97;
			if(!b[val]){
				b[val] = true;
				uniqueCount++;
			}
		}
		bool dead = false;
		for(int i=0; i< out.size(); i++){
			int val = out[i] - 97;
			//cerr << val << " " << b[val] << " " << g[val] << "\n";
			if(b[val])
				g[val] = true;
			else if(!wrong[val]){
				wrongCount++;
				wrong[val] = true;
			}
			
			if(checkifWon() == true) break;
		
			if(wrongCount == 7) { dead= true; break;}
		}
	
		if(checkifWon() == true) cout << "You win.\n";
		
		else if(dead == true)  cout << "You lose.\n";

		else cout << "You chickened out.\n";
	
	}


	return 0;
}