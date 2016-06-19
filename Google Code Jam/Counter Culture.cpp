#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("A-large-practice.in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    long long n;
    cin >> n;
    long long ans = 0;
    int d[42];
    int len = 0;
    while (n > 0) {
      d[len++] = n % 10;
      n /= 10;
    }
	
    while (len > 1 || (len == 1 && d[0] > 1)) {
	 
      if (d[0] == 0) {
        ans++;
        for (int i = 0; i < len; i++) {
          if (d[i] == 0) {
            d[i] = 9;
          } else {
            d[i]--;
            break;
          }
        }
        if (d[len - 1] == 0) {
          len--;
        }
        continue;
      }
      int half = (len + 1) / 2;
      bool rev = true;
      for (int j = 0; j < half; j++) {
        if ((j == 0 && d[j] != 1) || (j != 0 && d[j] != 0)) {
          rev = false;
        }
      }
	  
      if (rev) {
        rev = false;
        for (int j = 0; j < len - j - 1; j++) {
          if (d[j] != d[len - j - 1]) {
            rev = true;
            break;
          }
        }
      }
      ans++;
	  
      if (rev) {
        for (int j = 0; j < len - j - 1; j++) {
          swap(d[j], d[len - j - 1]);
		}
      } else {
        d[0]--;
      }
    }
    ans++;
    cout << ans << endl;
    cerr << "test " << qq << " done" << endl;
  }
  return 0;
}
