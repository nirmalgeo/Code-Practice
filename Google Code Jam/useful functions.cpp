inline int pow(int x, int n) {
	if (n == 0) return 1;
	if (n % 2 != 0) return x * pow(x, n - 1);
	int st = pow(x, n/2);
	return st * st;
}

inline long long tobase(string s, int base, int ascii[]){
	long long ans = 0;
	int temp;
	REP(i, s.length()){
		temp = ascii[s[i]];
		ans = ans* base;
		ans += temp;
	}
	return ans;
}
