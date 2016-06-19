//uva 514 simple use case of using stack and queue

#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    int n, x;

    while(cin>>n && n)
    {
        while(cin>>x && x)
        {
            stack<int>in;
            queue<int>out;

            for(int i=1;i<=n;i++)
            {
                if(i>1) cin>>x;

                out.push(x);
                in.push(i);		
				
                while(!in.empty() && !out.empty() && in.top()==out.front())
                {
                    in.pop();
                    out.pop();
                }
            }
            if(in.empty()) cout<<"Yes\n";
            else cout<<"No\n";
        }
        cout <<"\n";
    }
return 0;
}