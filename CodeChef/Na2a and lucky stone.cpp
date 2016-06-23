#include<bits/stdc++.h>
using namespace std;


int checkzerotrailing(int value)
{
	int count =0;
	while(! (value >> 1))
	{
		count++;
	}
	return count;

}

int main()
{
	long long n,a;
	cin >>n;
	for(int i=0; i < n;i++)
	{
		cin >> a;		
		long long temp =  a%10;
		
		if(temp == 5)
		{
				string multiplier = "4";
				long long oldValue , newvalue;
				int count =0;
				do 
				{
					oldValue = a * atoi( multiplier.c_str());
					count = checkzerotrailing(oldValue);
					//value = a/atoi( multiplier.c_str());
					multiplier = multiplier + "4";
					newvalue = a * atoi( multiplier.c_str());
				}while(checkzerotrailing(newvalue) > count)  ;
				
				
		
				cout << oldValue <<  "\n";
		
		}
		
		else
			
				cout<< a << "\n";
			
	
	}


	return 0;
}

