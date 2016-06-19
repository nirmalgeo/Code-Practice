#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	int n,m;
	long long int a;
	while(t--)
	{
		scanf("%d%d",&n,&m);
		assert(1<=n && n<=100000);
		assert(1<=m && m<=100000);
		set<long long> s;
		while(n--)
		{
			scanf("%ld",&a);
			assert(0<= a && a<= 1000000000000);
			s.insert(a);
		}
		
		while(m--)
		{
			scanf("%ld",&a);
			if(s.find(a) != s.end())
				printf("YES\n");
			else
				printf("NO\n");
			s.insert(a);
		
		}
	}

	return 0;
}