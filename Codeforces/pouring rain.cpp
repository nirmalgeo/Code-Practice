#include<bits/stdc++.h>
#define M_PI           3.14159265358979323846 
#define form_value(h, v, d, e) (( (4*h*v)/(d*M_PI)) - e)
using namespace std;
int main(){
	
	double d, h, v, e;
	cin >> d >> h >> v >> e;
	
	double ans = 1/form_value(h,v,d,e);
	
	if(ans < 0) cout << "NO\n";
	else {
		printf("YES\n");
		printf("%0.12lf",ans);
	}

	return 0;
}