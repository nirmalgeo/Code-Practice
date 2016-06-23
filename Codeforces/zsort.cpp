#include<bits/stdc++.h>
using namespace std;

struct arr{
	long long values;
	int index; 
};

typedef struct arr Obj;
bool cmp( Obj o1, Obj o2){

	//cout << o1.values << " " << o2.values << "\n";
	
	if(o1.index%2 != o2.index%2)
		return false;
	
	else if(o1.index%2 == o2.index%2 && o1.index == 1)
		return o1.values >= o2.values;
		
	else if(o1.index%2 == o2.index%2 && o1.index == 0)
		return o1.values <= o2.values;
}

int main(){
	int n;
	cin >> n;
	vector<Obj> v;
	
	for(int i=0; i<n; i++){
		Obj a;
		cin >> a.values;
		a.index = i;
		v.push_back(a);
	}
	
	sort(v.begin(), v.end(), cmp);

	for(const auto &c: v)
		cout << c.values <<  " " ;
	return 0;
}