#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<b;i++)
using namespace std;

char a[20][20];
bool row[10], column[10], leftdiag[20], rightdiag[20];
int main()
{
	char temp;
	int count =0;
	bool flag= true;
	FOR(i,1,9)
	{
		FOR(j,1,9)
		{
			cin>>temp;
			a[i][j]=temp;
			if(temp == '*')
			{
				count++;
				if(row[i] || column[j] || leftdiag[i+j-1])
				{
					flag=false;
				}
				
				else if( i<=j && rightdiag[abs(abs(i-j)-8)])
				{
					flag =false;
				}
					
				else if( i>j && rightdiag[abs(abs(i-j)+8)])
				{
					flag =false;
				}
					
				else
				{
					row[i] = true;
					column[j] = true;
					leftdiag[i+j-1] = true;
					if(i<=j)
						rightdiag[abs(abs(i-j)-8)] = true;
					else
						rightdiag[abs(abs(i-j)+8)] = true;
				}	
			}
		}
	}
	if(count != 8)
		cout<<"invalid"<<"\n";
	else if(!flag)
		cout<<"invalid"<<"\n";
	else
		cout<<"valid"<<"\n";
		

	return 0;
}