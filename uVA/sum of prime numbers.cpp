#include<bits/stdc++.h>
#define MAX 10000
using namespace std;
vector<int> primes;
bitset<10000010> bs;
vector<int> SumCount;


void sieve(int upperbound) {
	int _sieve_size = upperbound + 1;
	bs.set();
	bs[0] = bs[1] = 0; 
	for (int i = 2; i <= _sieve_size; i++) 
		if (bs[i]) {
			for (int j = i * i; j <= _sieve_size; j += i)
				bs[j] = 0;
			primes.push_back((int)i); 
		} 
}

void Calculate(){
	SumCount.resize(MAX+1);
	fill(SumCount.begin(), SumCount.end(), 0);
	int n = primes.size();
	for(int i=0; i < n ; i++){
		int sum = 0;
		for(int j=i; j < n; j++){
			sum += primes[j];
			if(sum > MAX)
				continue;
			SumCount[sum]++;
		}
	}
}


int main(){

	sieve(10000);
	Calculate();
	
	int val;
	while(scanf("%d", &val) && val){
		printf("%d\n", SumCount[val]);
	}

	return 0;
}