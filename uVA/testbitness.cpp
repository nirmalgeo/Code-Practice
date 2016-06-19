#include<bits/stdc++.h>
using namespace std;
int main(){
	int i;
	try {
		long long  x =0;
		for( i = 0 ; i < 64 ; i++)
		{
			x = 1 << i;
			cerr << x  << " " << i << "\n";
		}
	}
	
	catch(...){
		cout << "Exception  found.. value of i " << i ;
	}


	return 0;
}