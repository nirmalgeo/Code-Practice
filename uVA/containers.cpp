#include<bits/stdc++.h>
using namespace std;
int main(){

	ios_base::sync_with_stdio(0);cin.tie(0);
    int tc, kk=1, n, vis[1005];
    string s;
    char ch;
    while(cin>>s && s!="end"){
        memset(vis, 0 , sizeof(vis));
        int cnt=0, sl=s.size();
        for(int i=0;i<sl;i++)
            if(!vis[i])
            {
                vis[i]=1;
                cnt++;
                int prev = i;
                for(int j=i+1;j<sl;j++)
                    if(s[prev]>=s[j] && !vis[j])
                        prev=j, vis[j]=1;
            }
        cout<< "Case "<<kk++<<": "<<cnt <<"\n";
    }
	return 0;
	
}
