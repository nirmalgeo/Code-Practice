#include<bits/stdc++.h>
using namespace std;
int main()
{
	double h,u,d,f;
	
	while(1)
	{
		cin>>h>>u>>d>>f;
		if(h==0)
			break;
		assert(h>=1 && h<=100);
		assert(u>=1 && u<=100);
		assert(d>=1 && d<=100);
		assert(f>=1 && f<=100);
		
		double totDistance = 0;
		double fatigue = u*f/100;
		
		int count = 1;
		bool lost = false;
		while(totDistance<=h){
			
			totDistance = totDistance + u;
			if(totDistance > h){
				break;
			}
			totDistance = totDistance - d;
			
			//cerr << totDistance << " " << u <<  " " << d <<"\n";
			if(totDistance < 0){
				lost = true;
				break;
			}

			u = u - fatigue;
			if(u<0)
				u=0;
			count++;
		}
		
		if(lost)
			cout << "failure on day "<<count<<"\n";
		else
			cout << "success on day "<<count<<"\n";
	}
	return 0;
}