//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};

priority_queue<int> green, blue;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	//freopen("in.txt","r", stdin);
	//freopen("out","w",stdout);
	
	int t;
	cin >> t;
	
	while(t--)
	{
	

// code starts here 
	
		long long b,sg, sb, temp;
		cin >> b >> sg >> sb;
		green = priority_queue <int>(); 
		blue = priority_queue <int>(); 
		
		
		for(int i=0; i<sg; i++)
		{
			cin >> temp;
			green.push(temp);
		}
		
		
		for(int i=0; i<sb; i++)
		{
			cin >> temp;
			blue.push(temp);
		}
		
		while(true)
		{
			if(green.empty() && blue.empty())
			{
				cout << "green and blue died\n";
				break;
			}
			
			else if(!green.empty() && blue.empty())
			{
				cout << "green wins\n";
				while(!green.empty())
				{
					cout << green.top() <<"\n";
					green.pop();
				}
				break;
			}
			
			else if(green.empty() && !blue.empty())
			{
				cout << "blue wins\n";
				while(!blue.empty())
				{
					cout << blue.top() << "\n";
					blue.pop();
				}
				break;
			}
			for(int i=1; i<=b ; i++)
			{
				int a = -1, b = -1;
				if(!green.empty() && !blue.empty())
				{
					a = green.top();
					b = blue.top();					
					green.pop();
					blue.pop();
					if( a== b) ;
					else if( b == max(a,b))  blue.push(b-a);
					else green.push(a-b);
				}
			}
		}
		
// code ends here 
		if(t)	cout << "\n";
	}
	return 0;
}