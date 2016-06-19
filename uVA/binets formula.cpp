#include<bits/stdc++.h>
using namespace std;
double binet(unsigned int n)
{
    static const double phi = (1 + sqrt(5))*0.5;
    double fib = (pow(phi,n) - pow(1-phi,n))/sqrt(5);
    return round(fib);
}

int main(){
	int n;
	cin>>n;
	cout <<  binet(n);

	return 0;
}