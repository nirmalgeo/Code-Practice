#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define pi acos(-1.0)
#define N 1000000
#define long long LL
using namespace std;
 
int main ()
{
    int n,m;
    int counter=0;
   while(true)
   {
       cin >> m >> n;
       if (n ==0 && m ==0) break;
       counter++;
       if (counter > 1) cout << '\n';
       int field[102][102] = {0};
      for (int i=1; i<m+1; i++)
          for (int j=1; j<n+1; j++)
          {
              char temp;
              cin >> temp;
              if (temp == '*')
                  {
                      //111
                      //1*1
                      //111
                      field[i][j] = -1;
                      if (field[i-1][j] != -1) field[i-1][j]++; //top
                      if (field[i-1][j-1] != -1) field[i-1][j-1]++; //top left
                       if (field[i-1][j+1] != -1) field[i-1][j+1]++; //top right
                      if (field[i][j-1] != -1) field[i][j-1]++;//left
                      if (field[i+1][j] != -1) field[i+1][j]++; // bottom
                      if (field[i+1][j+1] != -1) field[i+1][j+1]++; //bottom right
                      if (field[i+1][j-1] != -1) field[i+1][j-1]++; //bottom right
                      if (field[i][j+1] != -1) field[i][j+1]++; //right
                  }
          }
 
           cout << "Field #" << counter << ":\n";
            for (int i=1; i<m+1; i++)
           {
 
                for (int j=1; j<n+1; j++)
                    {
                        if (field[i][j] == -1) cout << '*';
                        else cout << field[i][j];
                }
                cout << "\n";
           }
 
   }
 
    return 0;
}