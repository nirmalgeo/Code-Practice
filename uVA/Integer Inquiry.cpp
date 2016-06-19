#include<bits/stdc++.h>
using namespace std;
int main()
{
	list<char> sum;
	string line;
	int carry  = 0;
	list<char>::iterator it = sum.begin();
	
	for(int i=0;i <=110;  i++)
	{
		sum.insert(it, '0');
		it++;
	}

	while(getline(cin,line) && line!= "0")
	{
		reverse(line.begin(), line.end());
		it = sum.begin();

		for(int i=0; i<line.size(); i++)
		{
			int a = line[i] - 48;

			int b = *it- 48;			
			int c = a + b + carry;
			if( c>9)
			{
				carry = 1;
				c = c % 10;
			}
			char ch = c+48;
			*it = ch;
			
			//cout  << a <<" " <<  b  << " " << c <<  " " << carry << " " << *it << "\n";
			it++;
			
		}
	}
	if(carry == 1)
		sum.insert(it, '1');
	
	reverse(sum.begin(), sum.end());
	
	bool flag = false;
	for(auto c : sum)
	{
		if(c != '0')
			flag = true;
		
		if(flag)
			cout << c ;
	}
	return 0;
	
}