//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-large.in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){	
	
// code starts here 
		long long n, temp, rem, ans;
		cin >> n;
		int arr[10];
		int count=0;
		bool infi = false;
		int i = 1;

		memset(arr, -1, sizeof(arr));
		
		while(true){		
			temp = i*n;
			ans = temp;
			if(n == 0 || i>=30000) { infi = true; break; }
			
			while(temp > 0){
				rem = temp%10;
				arr[rem]=1;				
				temp/=10;
			}
			
			// check if all digits filled 
			bool flag = true;
			for(int j=0; j<10; j++)
				if(arr[j] == -1){
					flag = false;
					break;
				}
		
			if(flag) break;	
			i++;
		}
		

// code ends here 
	if(infi)
	cout << "Case #"<< cas << ": "<< "INSOMNIA" <<"\n";
	else
	cout << "Case #"<< cas << ": "<< ans <<"\n";	

	}

	return 0;
}