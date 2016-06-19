#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int n;
	cin >> n;
	vector<int> v, sum;
	v.resize(n);
	for(int i=0; i < n ; i++)
		cin >> v[i];
		
	sort(v.begin(), v.end());

	for(int i=0; i<n; i++)
		for(int j=0; j<n && j!=i; j++)
			sum.push_back(v[i]+v[j]);
	
	sort(sum.begin(), sum.end());
	
	int cnt=0;
	while(true){
		int cases;
		cin >> cases;
		if(cases == 0) break;
		cout << "Case #"<< ++cnt << ":\n";
		for(int cas =1; cas <= cases; cas++){
		
	// code starts here 
			int temp, ans;
			cin >> temp;
			
			for(auto &c: sum)
				if(c > temp) {
					if(abs(c-temp) < abs(ans-temp)) ans = c;
					break;
				}
				else
					ans = c;
		
	// code ends here 

		
		cout << "Closest sum to "<<temp << " is " << ans << ".\n";

		}
	
	}

	return 0;
}