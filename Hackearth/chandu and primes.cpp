#include<bits/stdc++.h>
#define INF 1000000
using namespace std;
typedef long long ll;
int arr[INF+1];

ll _sieve_size; 
bitset<10000010> bs; 
vector<int> primes; 

void sieve(ll upperbound) { 
	_sieve_size = upperbound + 1;
	bs.set();
	bs[0] = bs[1] = 0; 
	for (ll i = 2; i <= _sieve_size; i++) if (bs[i]) {
	for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
	primes.push_back((int)i); 
	} 
} 
bool isPrime(ll N) { 
	if (N <= _sieve_size) return bs[N]; 
	for (int i = 0; i < (int)primes.size(); i++)
	if (N % primes[i] == 0) return false;
	return true; 
}


int main() {
	sieve(1000000); 
	//build table
	for(int num = 1 ; num <= INF; num++){
		if(isPrime(num)){
			arr[num]++;
			arr[num+1] = arr[num];
			continue;
		}
		int inter = num;
		int div = INF;
		while(div > inter){
			div = div/10;
		}
		
		int rem;
		inter = num;
		while(inter > 0){
			rem = inter%div;
			if(rem == 0)
				break;
			if(isPrime(rem)){
				arr[num]++;
				break;
			}
			inter = rem;
			div = div/10;
		}
		arr[num+1] = arr[num];
	}
	
	
	int q;
	cin>>q;
	while(q--){
		int a,b;
		cin>>a >> b;
		cout << arr[b]- arr[a]<<"\n";
	}
	return 0;
} 


