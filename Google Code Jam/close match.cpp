//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (long long)1e18
#define REP(i,a,b) for(int i=a; i<b; i++)
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
typedef long long ll;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("B-small-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){
	
// code starts here 

		string a, b;
		
		cin >> a >> b;
		
		REP(i, 0, a.length()){
			if(a[i] == '?' && b[i] == '?')
				a[i] = b[i] = '0';
			else 
				break;
		}
		
		//cout << a << " " << b << "\n";
		
		char ch = 's';
		
		REP(i, 0 , a.length()){
			if(ch == 's'){
				if(a[i]==b[i] && a[i] == '?')
					a[i] = b[i] = '0';
				else if(a[i] != b[i] && a[i] == '?')
					a[i] = b[i];
				else if(a[i] != b[i] && b[i] == '?')
					b[i] = a[i];
			}
			if(a[i] != '?'){
				if(a[i] > b[i]){ ch = 'a'; break; }	
				else if(b[i] > a[i]) { ch = 'b'; break; }
			}	
		}
		
		REP(i, 0 , a.length()){
			if(a[i] == '?' && b[i] == '?' && ch == 's'){
				a[i] = b[i] = '0';
			}
			else if(a[i] == '?' && b[i] == '?' && ch == 'a'){
				a[i] = '0';
				b[i] = '9';
			}
			else if(a[i] == '?' && b[i] == '?' && ch == 'b'){
				a[i] = '9';
				b[i] = '0';
			}
					
			else if(a[i] == '?' && ch == 'a'){
				a[i] = '0';
			}
			else if(a[i] == '?' && ch == 'b'){
				a[i] = '9';
			}
			else if(b[i] == '?' && ch == 'a'){
				b[i] = '9';
			}
			else if(b[i] == '?' && ch == 'b'){
				b[i] = '0';
			}
		}
// code ends here

	
	 cerr << "test " << cas << " done" << endl;

	cout << "Case #"<< cas << ": "<< a << " " << b <<"\n";


	}

	return 0;
}