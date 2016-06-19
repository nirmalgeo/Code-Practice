//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice (1).in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	
// code starts here 
		int l,d,n;
		cin >> l >> d >> n;
		
		string words[d];
		
		for(int i=0; i<d; i++)  cin>> words[i];
		
		// group vertically rather than horizontally -- for permutation check
		
		for(int cas =1; cas <= n; cas++){
			
			string s;
			cin >> s;
			
			bool check[15][26];
			memset(check, false, sizeof check);
			int cnt = 0 ;
			
			for(int i=0; i< s.length(); i++){
				if(s[i] == '('){
					while(s[++i] != ')')
						check[cnt][s[i]-'a'] = true;
					cnt++;
				}
				else
				{
					check[cnt][s[i]-'a'] = true;
					cnt++;
				}
			}
		
			bool found ;
			int ans = 0;
			for(int i=0; i<d; i++){
				found = true;
				for(int j=0; j<l; j++){
					if(!check[j][words[i][j]-'a']){
						found = false;
						break;
					}
				}
				if(found) ans++;
			}
		
			cout << "Case #"<< cas << ": "<< ans <<"\n";	
		}


// code ends here 

	


	

	return 0;
}