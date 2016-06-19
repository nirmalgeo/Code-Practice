#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		char from[2], to[2];
		scanf(" %c %c %c %c",&from[0],&from[1], &to[0], &to[1]);
		int sourcei, sourcej, desti, destj;
		sourcei= from[0] - 64;
		sourcej= from[1]-  48 ;
		desti = to[0] - 64;	
		destj = to[1] - 48 ;
	
		//cout << sourcei <<" " << sourcej << " " << desti << " " << destj;
		if( sourcei > 8 || sourcej > 8 || desti >8 || destj > 8 || sourcei < 1 || sourcej < 1 || desti < 1 || destj < 1)
		{
			cout << "Impossible\n";
			continue;
		}
		
		int rightdiag = sourcei+sourcej-1;
		int leftdiag ;
		
		if(desti > destj )
			leftdiag = abs(abs(desti-destj)-8);
		else
			leftdiag = abs(abs(desti-destj)+8);
			
		
		int i= sourcei, j = sourcej;
		bool found = false;
		int count =0;
		while(i>0 && j <=8)
		{
			int right =  i+j-1;		
			int left;
			if( i > j)
				left = abs(abs(i-j)-8);
			else
				left = abs(abs(i-j)+8);
			
			if( right == rightdiag && left == leftdiag)
			{
				found = true;
				break;
			}
			count++;
			i--;
			j++;
		}
		
		if(!found)
		{
			i = sourcei;
			i = sourcej;
			int count =0;	
			while(i<=8 && j > 0)
			{
				
				int right = (i+j)-1;
				int left;
				if( i > j)
					left = abs(abs(i-j)-8);
				else
					left = abs(abs(i-j)+8);
				
				if( right == rightdiag && left == leftdiag)
				{
					found = true;
					break;
				}
				i++;
				j--;
				count++;
			}
		}
		
		if(!found)
			cout << "Impossible\n";
		else if(count == 0)
			cout << count << " " << static_cast<char>(i+64) << " " << j << "\n" ;
		else
			cout << "2 "<< from[0] << " " << from[1] << " "<< static_cast<char>(i+64) << " " << j << " " << to[0] << " " <<to[1] << "\n" ;
		
	}
	return 0;
}