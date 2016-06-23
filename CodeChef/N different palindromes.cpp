#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int n;
		scanf("%d", &n);
		char ch = 'a';
		string s = "";
		
		for(int i=1; i<=n; i++){
			s+= ch;
			ch++;
			int temp = ch;
			if(temp == 123)
				ch = 'a';
		}
		
		cout << s << "\n";
	
	}


	return 0;
}