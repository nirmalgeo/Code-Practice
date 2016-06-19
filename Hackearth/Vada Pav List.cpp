#include<bits/stdc++.h>
using namespace std;
int m[27][27][27][27][27];


int main()
{

	int n,a,b,c,d,e,count=0;
	cin>>n;
	int i,j,k,l,n;

	
	while(n--)
	{
		char s[10];
		scanf("%s",s);
		 a=0,b=0,c=0,d=0,e=0;
		
		
		 k =strlen(s);
		for(j=0;j<k;j++)
		{
			if(j==0)
				a= s[j]-'a' + 1;
			 if(j==1)
				b= s[j]-'a' + 1;
			 if(j==2)
				c= s[j]-'a' + 1;
			 if(j==3)
				d= s[j]-'a' + 1;
			 if(j==4)
				e= s[j]-'a' + 1;
		}
		
		if(!m[a][b][c][d][e])
			count++;
		m[a][b][c][d][e] = 1;
	}
	
	cout << count << endl;
	
	 for(i=0;i<27;i++)
        for(j=0;j<27;j++)
            for(k=0;k<27;k++)
                for(l=0;l<27;l++)
                    for(n=0;n<27;n++)
							if( m[i][j][k][l][n])
							{
								if(i)
									printf("%c", 'a' + i -1);
								if(j)
									printf("%c",  'a' + j -1);
								if(k)
									printf("%c",  'a' + k -1);
								if(l)
									printf("%c",  'a' + l -1);
								if(n)
									printf("%c",  'a' + n -1);	
								cout << "\n";
							}
							
								
	
	return 0;
}