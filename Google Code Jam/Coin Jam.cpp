//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


long long convertBinaryToBase(int x, int base) {
  // Some languages have built-ins which make this easy.
  // For example, in Python, we can avoid recursion and
  // just return int(bin(x)[2:], base)
  if (x == 0)
    return 0;
  return base * convertBinaryToBase(x / 2, base) + (x % 2);
}

long long findFactor(long long k) {
  for (long long d = 2; d * d <= k; d++)
    if (k % d == 0)
      return d;
  return 0;
}

void printCoins(int N, int X) {
  for (long long i = (1 << N-1) + 1; X > 0; i += 2) {
	cout << i << "\n";
    vector<long long> factors;
    for (int base = 2; base <= 10; base++) {
      long long x = convertBinaryToBase(i, base);
      long long factor = findFactor(x);
      if (!factor)
        break;
      factors.push_back(factor);
    }
    if (factors.size() < 9)
      continue;

    cout << convertBinaryToBase(i, 10);
    for (long long factor : factors)
      cout << " " << factor;
    cout << endl;
    X -= 1;
  }
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){
	

// code starts here 
	int N, X;
	cin >> N >> X;



// code ends here 

	cout << "Case #"<< cas << ":\n";
	printCoins(N, X);



	}

	return 0;
}