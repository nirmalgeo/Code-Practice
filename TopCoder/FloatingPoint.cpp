#include<bits/stdc++.h>
using namespace std;

class FloatingPoint{

	public:
	int representations(int number, int mantissa, int exponent)
	{
		int man = pow(2, mantissa) -1;
		int exp = pow(2, exp) - 1;
		long long val;
		int count = 0;
		for(int i=1;i<= man;i++)
		{
			for(int j=exp; j>=0; j --)
			{
				val = i * pow(2,exp);
				if( val == number)
					count++;
			}
		}
		return count;
	}
};	
