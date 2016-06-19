//nirmalgeo25 template
#include<bits/stdc++.h>
#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};

string arr[51];
int N,K;

inline bool checkWinner(char ch){
	
	REP(i,N) REP(j,N) REP(k,8){
			bool bad = false;
			REP(l,K){
				int x = i + xarr[k] * l, y = j + yarr[k] * l;
				if(x < 0 || x >= N || y < 0 || y >= N || arr[x][y] != ch) {bad = true; break;}
			}
			if(!bad) return true;
		}
	
	return false;

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large-practice.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int ans=0;
		string answer;
		
		cin >> N >> K;		
		
		for(int i=0; i<N; i++) cin >> arr[i];
		
		for(int i=0; i<N; i++){
			string temp  = "", front = "";
			for(int j=0; j<N; j++){
				if(arr[i][j] != '.')
					temp+= arr[i][j];
			}
			int len = temp.length();
			for(int t=0; t < (N-len); t++) front += ".";
			
			arr[i] = front + temp;
			//cout << arr[i] << "\n";
		}
		
		if(checkWinner('B')) { ans++; answer = "Blue"; }
		if(checkWinner('R')) { ans++; answer = "Red";  }
		
// code ends here 
	if(ans == 0) answer = "Neither";
	if(ans == 2) answer = "Both";
	

	cout << "Case #"<< cas << ": "<< answer <<"\n";


	}

	return 0;
}