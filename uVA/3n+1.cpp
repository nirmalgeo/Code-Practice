#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	int i,j;
  
	while (	scanf ("%d %d", &i, &j) != EOF ) {
	
		cout << i <<" " <<  j << " "; 
		if(i > j) swap(i,j);
		int max_length=0;
		
		
		while(i<=j){
			int cycle_length=1;
			int n=i;
			while(n > 1)
			{
				if(n%2 == 1) {
					n = (3*n)+1;
					n >>=1;
					cycle_length+=2;
				}
				
				else{
					n>>=1;
					cycle_length++;
				}
			}
							
			if ( cycle_length > max_length)
				max_length=cycle_length;		
			i++;
		}
		cout << max_length << "\n";
	}
	return 0; 
}
