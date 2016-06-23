#include<iostream.h>
#include<vector.h>
#include<stdlib.h>
using namespace std;
int main()
{
	int n,a;
	cin >> n;
	vector<int> v;
	for(int i=0;i<n;i++)
	{
		cin>>a;
		v.push_back(a);
	}
	
	for(int i=0; i < n; i++)
	{
		int ma=0,mb=0;
		if( i+1 < n)
			mb= abs(v[i+1] - v[i]);
		if( i-1 >= 0 )
			ma = abs(v[i] - v[i-1]);
		
		if(ma == 0)
			cout << mb << " ";
		else if(mb == 0)
			cout << ma << " ";
		else if(ma <= mb )
			cout << ma << " ";
		else
			cout << mb << " ";
			
		mb = abs(v[n-1] - v[i]);
		ma = abs(v[0] - v[i]);
		if( mb> ma)
			cout <<mb <<"\n";
		else
			cout <<ma <<"\n";	
	}
	return 0;
}