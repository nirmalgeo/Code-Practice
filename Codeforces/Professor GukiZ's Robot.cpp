#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long x1 , x2, y1, y2, count = 0;
	scanf("%lld %lld", &x1 , &y1);
	
	scanf("%lld %lld", &x2 , &y2);
	
	
	while(1){
		if(x1 == x2 && y1 == y2)
			break;
		
		if(x2 > x1 &&  y2 >  y1){
			count++;
			x2--;
			y2--;
		}
		
		else if(x2 < x1 && y2 < y1){
			count++;
			x2++;
			y2++;
		}
		
		else if (x2 > x1 && y2 < y1){
		
		
		}
		
		else if(x2 > x1){
			count++;
			x2--;
		}
		else if(x2 < x1){
			count++;
			x2++;
		}
		else if(y2 > y1){
			count++;
			y2--;
		}
		else if(y2 < y1){
			count++;
			y2++;
		}
	}
	cout << count;



	return 0;
}