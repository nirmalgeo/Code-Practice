#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    //scanf("%d ",&n);
	cin>>n;
    assert(n>=1 && n<=100);
    string line[8]={"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
	cin.ignore();
    for(int i=1;i<=n;i++){
        string s;
		
        getline(cin,s);
        cout << "Case #"<<i<<": ";
        assert(s.length() <= 1000);
        int last = -1;
        for(int j=0;j<s.length();j++){
            assert(s[j] == ' ' || (s[j]>=97 && s[j] <=122));
            if(s[j] == ' ') {
                if(last == 0)
                    cout << " ";
                cout << "0";
                last = 0;
                continue;
            }
            else {
                int posi,posj;
                for(int a=0;a<8;a++){
                    for(int b=0;b<line[a].length();b++){
                        if(s.at(j) == line[a][b]){
                            posi=a;
                            posj=b;
                            break;
                        }
                    }
                }
                posi+=2;
                posj++;
                if(last == posi)
                    cout << " ";
                
                while(posj--){
                    cout << posi ;
                }
                last = posi;
            }
        }
        
        cout << "\n";
    
    }

    return 0;
}