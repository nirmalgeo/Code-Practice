#include <iostream>
#include <bitset>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;

ll _sieve_size;
bitset<10000010> bs;   
vi primes;   

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a * (b / gcd(a, b)); }

void sieve(ll upperbound) {         
  _sieve_size = upperbound + 1;     
  bs.set();                         
  bs[0] = bs[1] = 0;                
  for (ll i = 2; i <= _sieve_size; i++) if (bs[i]) {
    for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
    primes.push_back((int)i);  
} }                            

bool isPrime(ll N) {                
  if (N <= _sieve_size) return bs[N];
  for (int i = 0; i < (int)primes.size(); i++)
    if (N % primes[i] == 0) return false;
  return true;                    
}                      


ll numDiffPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
  while (N != 1 && (PF * PF <= N)) {
    if (N % PF == 0) ans++;                        
    while (N % PF == 0) N /= PF;
    PF = primes[++PF_idx];
  }
  if (N != 1) ans++;
  return ans;
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  sieve(1005);
  
  while(t--){
	int a, b;
	cin >> a >> b;
	int val = lcm(a,b);
	if(isPrime(numDiffPF(val))) cout <<"Yes\n";
	else	cout << "No\n";
  }
  return 0;
}
