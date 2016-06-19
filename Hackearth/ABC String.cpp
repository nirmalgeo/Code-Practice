#include<bits/stdc++.h>
#define FOR(i,a,b) for(long long i=a;i<b;i++)
#define modouput 1000000007
using namespace std;
// Find Stirling number second kind
int s_dynamic(int n,int k) {
    int maxj = n-k;

    int *arr = new int[maxj+1];

    for (int i = 0; i <= maxj; ++i)
        arr[i] = 1;

    for (int i = 2; i <= k; ++i)
        for(int j = 1; j <= maxj; ++j)
            arr[j] += i*arr[j-1];

    return arr[maxj];
}

int S(int n,int k)
{
	if(n<2)
		return 1;
	return (S(n-1,k-1) + k*(S(n-1,k)));
}

int main()
{
	long long t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n < 3)
			cout << 0<<"\n";
		else
		{
			cout << (6*S(n,3))%modouput <<"\n";
		}
	}
	return 0;
}