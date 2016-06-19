#include<bits/stdc++.h>
using namespace std;

#define SIZE(a) ((int)a.size())
int const MAX = 105;

int main(int argc, char **argv)
{
	int T; cin >> T;
	while (T-- != 0)
	{
		int stations; cin >> stations;
		int S, Q; cin >> S >> Q;
		queue<int> B[MAX];
		stack<int> carrier;
		for (int i = 0; i < stations; i++)
		{
			int size; cin >> size;
			for (int j = 0; j < size; j++)
			{
				int x; cin >> x;
				B[i].push(x - 1);
			}
		}
		int time = 0;
		for (int curStation = 0;; curStation = (curStation + 1) % stations)
		{
			while (!carrier.empty() && (carrier.top() == curStation || SIZE(B[curStation]) < Q))
			{
				if (carrier.top() != curStation)
					B[curStation].push(carrier.top());
				carrier.pop();
				time++;
			}
			while (!B[curStation].empty() && SIZE(carrier) < S)
			{
				carrier.push(B[curStation].front());
				B[curStation].pop();
				time++;
			}
			bool allEmpty = carrier.empty();
			for (int i = 0; i < stations && allEmpty; i++)
				allEmpty &= B[i].empty();
			if (allEmpty) break;
			time += 2;
		}
		cout << time << endl;
	}
	return 0;
}

