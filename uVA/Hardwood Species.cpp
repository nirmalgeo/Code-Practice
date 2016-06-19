#include<bits/stdc++.h>
using namespace std;

int main() {
	int n;
	map<string, int> Trees;
	char name[35];

	scanf("%d\n\n", &n);
	while (n--) {
		int total = 0;

		total = 0;
		while (gets(name)) {
			if (strlen(name) == 0)
				break;

			if (Trees.count(string(name)) == 0) {
				Trees[string(name)] = 1;
			} else
				Trees[string(name)] = Trees[string(name)] + 1;

			total++;
		}

		map<string, int>::iterator it;
		for (it = Trees.begin(); it != Trees.end(); it++) {
			printf("%s %.4lf\n", (*it).first.data(),
					(double) (*it).second / (double) total * 100.0);
		}
		if (n > 0){
			printf("\n");
			Trees.clear();
		}
	}

	return 0;
}