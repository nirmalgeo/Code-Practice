#include<bits/stdc++.h>
using namespace std;
vector<pair<long long, long long>> v;
inline long long countSetBits(long long n)
{
   long long count = 0;
    while (n)
    {
      n &= (n-1) ;
      count++;
    }
    return count;
}
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n;
		scanf("%d", &n);
		long long temp, count;
		for(int i=0; i<n; i++){
			scanf("%lld", &temp);
			count = countSetBits(temp);
			v.push_back({count,temp});
		}
		
		sort(v.begin(), v.end());
		
		for(auto &c:v)
			cout << c.second << " ";
		cout <<"\n";
	}

	return 0;
}