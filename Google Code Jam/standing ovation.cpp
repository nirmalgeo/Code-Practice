#include<bits/stdc++.h>
using namespace std;
int main(){
	
	freopen("in","r", stdin);
	freopen("out","w", stdout);	
	
    int cases;
    cin >> cases;
    for (int cas = 0; cas < cases; cas++)
    {
        int Sm;
        string freq;
        cin >> Sm >> freq;
        int ans = 0;
        int stand = 0;
        for (int i = 0; i <= Sm; i++)
        {
            if (freq[i] != '0' && stand < i)
            {
                ans += i - stand;
                stand = i;
            }
            stand += freq[i] - '0';
        }
        cout << "Case #" << cas + 1 << ": " << ans << "\n";
    }

	return 0;
}