#include<bits/stdc++.h>
using namespace std;
			int arr[25][25];

class  ChessFloor {
	public:
		int minimumChanges(vector <string> floor)
		{
			int n = floor.size();
	
			for(int i=0;i<n-1;i++)
			{
				for(int j=0;j<n-1;j++)
				{
					int count = 0;
					count = (floor[i][j] != floor[i+1][j])? 0: 1;
					count = (floor[i][j] != floor[i][j+1])? 0: 1;
					arr[i][j] = count;
				}
			}
			int count = 0;
			
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
				 if(!arr[i][j])
					count=count + arr[i][j];
			
			count = count/2;
			
			return count;
		}
};

int main()
{




	return 0;
}	